/*!
 * @brief Implementation for the test runner. Sanitises the environment and kicks
 * off the tests
 *
 * @author hmarcks
 *
 * @addtogroup Test Runner
 *
 * @date 13/01/19
 */
#include <condition_variable>
#include <utility/threadSafeT.h>
#include <utility/utility.h>

#include <threadPool/ThreadPool.h>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <testRunner/testRunner.h>
#include <safeList/safeList.h>
#include <iostream>
#include "testThread.h"

namespace TestRunner
{
TestRunner::TestRunner(std::string const& testfilePath
                       , PluginLoader::sharedMap_t<
    Communication::I_communication> commsInterfaces_in
                       , PluginLoader::sharedMap_t<
    Protocol::I_protocolInterface> protocolInterfaces_in
                       , std::unique_ptr<testAnalyser2::I_TestAnalyser2> TA_in
                       , ThreadHandler::ThreadPool& threadPool_in)
    : _testFilePath(testfilePath)
      , _TestAnalyser(std::move(TA_in))
      , _commsInterface(std::move(commsInterfaces_in))
      , _protocolInterface(std::move(protocolInterfaces_in))
      , _threadPool(threadPool_in)
      , _killThreadHandler(false)
      , _testFile(_GetTestFile(std::move(_TestAnalyser)))
{
}
/*!
 * @brief Will kick off and perform the testing
 * @todo needs more methods
 * @return true for successful, otherwise false
 */
bool TestRunner::BeginTesting()
{
    bool retval = true;

    /* Gets the plugin Spawners */
    /*!
     * @todo Set up multiple interfaces for the
     * threads (if wanted) so put me in a loop
     * @todo Move blocks into templated methods
     * @todo More plugins (thread handler, etc)
     * @todo exception for wrong config name
     */
    std::vector<std::shared_ptr<Communication::I_communication>> availableCommsInterfaces;
    {
        auto interfaceFactory =
            _commsInterface.at(_testFile.GetTestConfiguration()._commsHandler);

//        auto if_shr = std::make_shared<Communication::I_communication>(*interfaceFactory);
        availableCommsInterfaces.push_back(_commsInterface.at(_testFile.GetTestConfiguration()._commsHandler));
    }
    std::vector<std::shared_ptr<Protocol::I_protocolInterface>> availableProtInterfaces;
    {
        auto interfaceFactory =
            _protocolInterface.at(_testFile.GetTestConfiguration()._protocol);
//        auto prot_shr = std::make_shared<Protocol::I_protocolInterface>(interfaceFactory);
        availableProtInterfaces.push_back(_protocolInterface.at(_testFile.GetTestConfiguration()._protocol));
        //    availableProtInterfaces[0]->init_Protocol();
    }

    SafeContainers::safeList<Protocol::DataStruct> results;
    SafeContainers::safeList<int> resultCodes;

    const auto maxThreads = utility::StringToLong(_testFile.GetTestConfiguration()._maxThreads);
    const auto tps = utility::StringToLong(_testFile.GetTestConfiguration()._tps);
    const auto ratio = _GetRatio(tps
                           , maxThreads);
    /*! @todo Need to separate and edit for changing comms interfaces */
    for (auto i = 0L; i < maxThreads; ++i)
    {
        auto tfObj = std::make_shared<TestThread>(_killThreadHandler
                                                  , availableCommsInterfaces[0]
                                                  , availableProtInterfaces[0]
                                                  , results
                                                  , resultCodes
                                                  , ratio);
//        auto tfObj = new TestThread(_killThreadHandler
//                                    , availableCommsInterfaces[0]
//                                    , availableProtInterfaces[0]
//                                    , results
//                                    , resultCodes
//                                    , ratio);
        std::function<void(void)> testFunc = std::bind(&TestThread::StartTest
                                                       , tfObj);
        _threadPool.AddTaskToQueue(testFunc);
        _threadsVec.push_back(tfObj);
    }
    /* Poller */
    _WaitForThreads();

    std::cout << "Here I be" << std::endl;
    return retval;
}
/*!
 * @brief Access the internal kill thread handler
 * @param newVal The new value it should take
 * @return The value fo the killthreadhandler
 */
bool TestRunner::AccessKillThreadHandler(std::optional<bool> newVal)
{
    if (newVal.has_value())
    {
        _killThreadHandler.SetT(newVal.value());
    }

    return _killThreadHandler.GetT();
}
/*!
 * @brief Gets the test file from the test analyser
 * @param TAIn The test anaylser we're using
 * @return The testfile we want
 */
testAnalyser2::TestFile TestRunner::_GetTestFile(std::unique_ptr<testAnalyser2::I_TestAnalyser2> TAIn)
{
    testAnalyser2::TestFile newTF;
    TAIn->startAnalysis();

    if (TAIn->isAnalysed())
    {
        newTF = TAIn->GetTestFile();
    }

    return newTF;
}
/*!
 * @brief Calculates the sending ratio (transactions per microsecond
 * @param rate Transactions wanted per second
 * @param numOfThreads How many threads there are
 * @return How often each thread needs to fire in milliseconds
 */
int TestRunner::_GetRatio(long rate
                          , long numOfThreads)
{
    auto rate_dbl = static_cast<double>(rate);
    auto ratesPerThread = rate_dbl/numOfThreads;

    return (static_cast<int>(ratesPerThread*1000000));
}
/*!
 * @brief The handler for the asynchronous timer. Kills all threads.
 */
void TestRunner::_TimerHandler(const boost::system::error_code& e)
{
    _killThreadHandler.SetT(true);
}
/*!
 * @brief Sets up the timer and polls for the threads to finish
 */
void TestRunner::_WaitForThreads()
{
    /* Setup the asynchronous timer */
    auto runTime = utility::StringToLong(_testFile.GetTestConfiguration()._secondsDuration);
    boost::asio::io_context io;
    boost::asio::steady_timer t(io
                                , boost::asio::chrono::seconds(runTime));
    t.async_wait(boost::bind(&TestRunner::_TimerHandler
                             , this
                             , boost::asio::placeholders::error));
    io.run();
    /*
     * Now we must wait until either we're
     * told to die OR we run out of time
     */
    while (!_killThreadHandler.GetT())
    {
        sleep(1);
    }
    io.stop();
    /* Wait until all threads have finished */
    for (unsigned i = 0; i < _threadsVec.size(); ++i)
    {
        bool notAllDone = 0;
        /* If the thread is finished, remove it */
        if (!_threadsVec[i]->GetFinished())
        {
            notAllDone = 1;
        }
        /* adjust loop */
        if (i + 1 >= _threadsVec.size())
        {
            i = 0;
        }
        if (!notAllDone)
            break;
    }
    std::cout << "End of wait" << std::endl;
}
} /* namespace TestRunner */
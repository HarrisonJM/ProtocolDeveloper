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
#include "testThread.h"

namespace TestRunner
{
TestRunner::TestRunner(std::string const& testfilePath
                       , const PluginLoader::sharedMap_t<
    PluginLoader::I_Plugin<Communication::I_communication>>& commsInterfaces
                       , const PluginLoader::sharedMap_t<
    PluginLoader::I_Plugin<Protocol::I_protocolInterface>>& protocolInterfaces
                       , std::unique_ptr<testAnalyser2::I_TestAnalyser2> TAIn
                       , ThreadHandler::ThreadPool& threadPool_in)
    : _testFilePath(testfilePath)
      , _TestAnalyser(std::move(TAIn))
      , _commsInterface(commsInterfaces)
      , _protocolInterface(protocolInterfaces)
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
     */
    std::vector<std::shared_ptr<Communication::I_communication>> availableCommsInterfaces;
    {
        auto interfaceFactory =
            _commsInterface.get()->at(_testFile.GetTestConfiguration()._handler)()->createNewObject();
        availableCommsInterfaces.push_back(interfaceFactory);
        //    availableInterfaces[0]->init_Comms();
    }
    std::vector<std::shared_ptr<Protocol::I_protocolInterface>> availableProtInterfaces;
    {
        auto interfaceFactory =
            _protocolInterface.get()->at(_testFile.GetTestConfiguration()._protocol)()->createNewObject();
        availableProtInterfaces.push_back(interfaceFactory);
        //    availableProtInterfaces[0]->init_Protocol();
    }

    SafeContainers::safeList<Protocol::DataStruct> results;
    SafeContainers::safeList<int> resultCodes;

    long maxThreads = Utility::StringToLong(_testFile.GetTestConfiguration()._maxThreads);
    long tps = Utility::StringToLong(_testFile.GetTestConfiguration()._tps);
    long ratio = _GetRatio(tps
                           , maxThreads);
    /*! @todo Need to separate and edit for changing comms interfaces */
    for (long i = 0L; i < maxThreads; ++i)
    {
        auto tfObj = std::make_shared<TestThread>(_killThreadHandler
                                                  , availableCommsInterfaces[0]
                                                  , availableProtInterfaces[0]
                                                  , results
                                                  , resultCodes
                                                  , ratio);
        std::function<void(void)> testFunc = std::bind(&TestThread::StartTest
                                                       , tfObj);
        _threadPool.AddTaskToQueue(testFunc);
        _threadsVec.push_back(tfObj);
    }
    /* Poller */
    _WaitForThreads();

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
 * @brief Searches for the correct plugin, will fail.
 * @tparam IFType the protocol interface we want
 * @param pluginName The name of the plugin we want to use (gottenf rom the test configuration)
 * @return A const ref to the interface plugin factory
 */
template<typename IFType>
const std::function<std::shared_ptr<IFType>()>& TestRunner::_SearchForPlugin(const std::string& pluginName)
{
    return nullptr;
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

    return (static_cast<int>(ratesPerThread)*1000000);
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
    long runTime = Utility::StringToLong(_testFile.GetTestConfiguration()._secondsDuration);
    boost::asio::io_context io;
    boost::asio::deadline_timer t(io
                                  , boost::posix_time::seconds(runTime));
    t.async_wait(boost::bind(&TestRunner::_TimerHandler
                           , this
                           , boost::asio::placeholders::error));
    /*
     * Now we must wait until either we're
     * told to die OR we run out of time
     */
    while (!_killThreadHandler.GetT())
    {
        sleep(1);
    }
    /* Wait until all threads have finished */
    for (unsigned i = 0; i < _threadsVec.size(); ++i)
    {
        /* If the thread is finished, remove it */
        if (_threadsVec[i]->GetFinished())
        {
            _threadsVec.erase(_threadsVec.begin() + i);
        }
        /* adjust loop */
        if (i + 1 >= _threadsVec.size())
        {
            i = 0;
        }
    }
}
/*!
 * @brief Searches for the correct comms plugin
 * @param pluginName The name of the plugin we want to use (gotten from the test configuration)
 * @return A const ref to the interface plugin factory
 */
template<>
const std::function<std::shared_ptr<PluginLoader::I_Plugin<
    Communication::I_communication>>()>& TestRunner::_SearchForPlugin(const std::string& pluginName)
{
    auto& mapRef = _commsInterface;
    return (*mapRef).at(pluginName);
}
/*!
 * @brief Searches for the correct protocol plugin
 * @param pluginName The name of the plugin we want to use (gotten from the test configuration)
 * @return A const ref to the interface plugin factory
 */
template<>
const std::function<std::shared_ptr<PluginLoader::I_Plugin<
    Protocol::I_protocolInterface>>()>& TestRunner::_SearchForPlugin(const std::string& pluginName)
{
    auto& mapRef = _protocolInterface;
    return (*mapRef).at(pluginName);
}
} /* namespace TestRunner */
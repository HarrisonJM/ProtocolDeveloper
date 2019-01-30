/*!
 * @brief The test runner class itself.
 *
 * This class is responsible for setting up the test environment.
 *
 * Grabs the required plugins from the directory pointed to.
 * Creates the test objects
 * Sorts out the thread handling/branching method
 * Passes the test objects to where they are required
 * Pre-creates some values ready to send
 * Starts the test
 *
 * @author hmarcks
 *
 * @addtogroup Test Runner
 *
 * @date 13/01/19
 */

#ifndef PROTOCOLDEVELOPER_TESTRUNNER_H
#define PROTOCOLDEVELOPER_TESTRUNNER_H

#include <string>

#include <I_communication.h>
#include <I_protocolInterface.h>
#include <I_TestAnalyser2.h>

#include <pluginLoader/pluginLoader.h>
#include <boost/system/error_code.hpp>

#include <threadPool/ThreadPool.h>
#include <utility/threadSafeT.h>

namespace TestRunner
{
class TestThread;
/*!
 * @brief These codes define what aspects are missing to be passed in later
 * @{
 */
enum missingCodes_e
    : short
{
    MISS_NULL = 0x00, /*! < Nothing                               */
    MISS_PROT = 0x01, /*! < Protocol interface is missing         */
    MISS_COMM = 0x02, /*! < Communication interface is missing    */
    MISS_THRD = 0x04, /*! < Thread handler is missing             */
    MISS_TCAS = 0x08  /*! < Test case analyser schema is missing  */
};
/*!@}*/

/*!
 * @brief TestRunner class. "Implements" a testcase and other settings
 */
class TestRunner
{
public:
    /*!
     * @brief Constructor Sets up the environment
     * @param testfilePath The path to the testfile we wish to run
     * @param commsInterfaces A reference to the sharedMap of comms interfaces, for searching through
     * @param protocolInterfaces A reference to the sharedMap of Protocol Interfaces, for searching through
     * @param TAIn A unique pointer to the test case analyser
     */
    TestRunner(std::string const& testfilePath
               , const PluginLoader::sharedMap_t<
        PluginLoader::I_Plugin<Communication::I_communication>>& commsInterfaces
               , const PluginLoader::sharedMap_t<
        PluginLoader::I_Plugin<Protocol::I_protocolInterface>>& protocolInterfaces
               , std::unique_ptr<testAnalyser2::I_TestAnalyser2> TAIn
               , ThreadHandler::ThreadPool& threadPool_in);
    /*!
     * @brief Destructor
     */
    ~TestRunner() = default;
    /*!
     * @brief Kicks off the entirety of the testing
     * @return True for successful run, otherwise false
     */
    bool BeginTesting();
    /*!
     * @brief Access the internal kill thread handler
     * @param newVal The new value it should take
     * @return The value fo the killthreadhandler
     */
    bool AccessKillThreadHandler(std::optional<bool> newVal);
private:
    /*! @brief The full path to the testcase */
    const std::string _testFilePath;
    /*! The mutex used to control the testThreads */
    std::mutex _mutex;
    /*! @brief A reference to the test analyser, will also store our parsed test file*/
    std::unique_ptr<testAnalyser2::I_TestAnalyser2> _TestAnalyser;
    /*! @brief Shared map containing all the possible communication interface plugins we can use */
    const PluginLoader::sharedMap_t<PluginLoader::I_Plugin<Communication::I_communication>> _commsInterface;
    /*! @brief Shared map containing all the possible protocol interface plugins we can use */
    const PluginLoader::sharedMap_t<PluginLoader::I_Plugin<Protocol::I_protocolInterface>> _protocolInterface;
    // ThreadHandler
    /*! @brief the threadpool we'll be adding our tests to */
    ThreadHandler::ThreadPool& _threadPool;
    /*! @brief Controls whether the test needs to DIE */
    Utility::ThreadSafeT<bool> _killThreadHandler;
    /*! @brief Contains all the created threads */
    std::vector<std::shared_ptr<TestThread>> _threadsVec;
    /*! @brief The testfile itself */
    testAnalyser2::TestFile _testFile;

    /* METHODS */
    /*!
     * @brief Returns the test file from the analyser
     * @param TAIn The Test analyser
     * @return The compiled test file
     */
    testAnalyser2::TestFile _GetTestFile(std::unique_ptr<testAnalyser2::I_TestAnalyser2> TAIn);
    /*!
     * @brief Grabs the plugin we want from currently available plugins
     * @param pluginName The name of the plugin we want
     * @return The plugin factory function
     */
    template<typename IFType>
    const std::function<std::shared_ptr<IFType>()>& _SearchForPlugin(const std::string& pluginName);
    /*!
     * @brief Works out the ratio for sending data in milliseconds per thread
     * @param rate Transactions per second
     * @param numOfThreads The number of threads
     * @return
     */
    int _GetRatio(long rate
                  , long numOfThreads);
    /*!
     * @brief The total duration async timer handler
     * @param e The boost error code
     */
    void _TimerHandler(const boost::system::error_code& e);
    /*!
     * @brief Handles waiting for threads
     */
    void _WaitForThreads();
};

/* Specialized template prototypes */

/*!
 * @brief Grabs comms plugins
 * @param pluginName The anme of the plugin (as described in the testcase)
 * @return The plugin factory
 */
template<>
const std::function<
    std::shared_ptr<Communication::I_communication>()>& TestRunner::_SearchForPlugin(const std::string& pluginName);
/*!
 * @brief Grabs protocol plugins
 * @param pluginName The anme of the plugin (as described in the testcase)
 * @return The plugin factory
 */
template<>
const std::function<
    std::shared_ptr<Protocol::I_protocolInterface>()>& TestRunner::_SearchForPlugin(const std::string& pluginName);
} /* namespace TestRunner */

#endif /* PROTOCOLDEVELOPER_TESTRUNNER_H */

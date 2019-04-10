/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup testRunner
 * @{
 * @addtogroup interfaces
 * @{
 *
 * @date 09/04/19
 */
#ifndef PROTOCOLDEVELOPER_I_TESTRUNNER_H
#define PROTOCOLDEVELOPER_I_TESTRUNNER_H

#include <optional>
#include <pluginLoader/PluginLoaderCommon.h>
#include <I_communication.h>
#include <I_protocolInterface.h>
#include <I_TestAnalyser2.h>
#include <threadPool/ThreadPool.h>

namespace testRunner
{
/*!
 * @brief TestRunner class. "Implements" a testcase and other settings
 */
class I_testRunner
{
public:
    /*!
     * @brief Constructor
     */
    I_testRunner() = default;
    /*!
     * @brief Constructor Sets up the environment
     * @param testfilePath The path to the testfile we wish to run
     * @param commsInterfaces_in A reference to the sharedMap of comms interfaces, for searching through
     * @param protocolInterfaces_in A reference to the sharedMap of Protocol Interfaces, for searching through
     * @param TA_in A unique pointer to the test case analyser
     * @param threadPool_in a reference tot he threadpool we wish to use
     */
    I_testRunner(std::string const& testfilePath
                 , pluginLoader::sharedMap_t<
        Communication::I_communication> commsInterfaces_in
                 , pluginLoader::sharedMap_t<
        Protocol::I_protocolInterface> protocolInterfaces_in
                 , std::unique_ptr<testAnalyser2::I_TestAnalyser2> TA_in
                 , threadPool::ThreadPool& threadPool_in
                 , int64_t loggerID) {}
    /*!
     * @brief Destructor
     */
    ~I_testRunner() = default;
    /*!
     * @brief Kicks off the entirety of the testing
     * @return True for successful run, otherwise false
     */
    virtual bool BeginTesting() = 0;
    /*!
     * @brief Access the internal kill thread handler
     * @param newVal The new value it should take
     * @return The value fo the killthreadhandler
     */
    virtual bool AccessKillThreadHandler(std::optional<bool> newVal) = 0;
};
} /* namespace CHANGEME */
/*! @} @} */
#endif /* PROTOCOLDEVELOPER_I_TESTRUNNER_H */

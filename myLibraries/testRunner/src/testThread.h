/*!
 * @brief Header for a test thread. This is the thread that will actually be
 * run by the program that will send data to the target
 *
 * @author hmarcks
 *
 * @addtogroup testRunner
 * @{
 * @date 16/01/19
 */


#ifndef PROTOCOLDEVELOPER_TESTTHREAD_H
#define PROTOCOLDEVELOPER_TESTTHREAD_H

#include <condition_variable>

#include <I_communication.h>
#include <I_protocolInterface.h>
#include <safeList/safeList.h>

#include <testAnalyser2/testfile/dataPoint.h>
#include <utility/threadSafeT.h>
#include <I_testThread.h>

namespace testRunner
{
/*!
 * @brief A single test thread
 */
class TestThread
    : public I_TestThread
{
public:
    /*!
     * @brief Contructor
     * @param killThread_in A reference to the kill thread handler
     * @param commsInterface_in The comms that we are interfacing over
     * @param protocolInterface_in The protocol that we are using to generate data
     * @param resultsList_in Where to store the results
     * @param ratio_in The rough gap between firings we want
     */
    TestThread(const utility::ThreadSafeT<bool>& killThread_in
               , std::shared_ptr<Communication::I_communication>& commsInterface_in
               , std::shared_ptr<Protocol::I_protocolInterface>& protocolInterface_in
               , safeContainers::safeList<Protocol::DataStruct>& resultsList_in
               , safeContainers::safeList<int>& codeList_in
               , long ratio_in
               , int64_t loggerID
               , int threadID);
    /*!
     * @brief Destructor
     */
    ~TestThread() = default;
    /*!
     * @brief Performs the test
     */
    void StartTest() override;
    /*!
     * @brief Returns whether or not the thread is finished (threadsafe)
     * @return the internal finished boolean
     */
    bool GetFinished() override;
    /*!
     * @brief Sets the internal finished boolean (threadsafe)
     * @param newVal What to set the finished boolean to
     */
    void SetFinished(bool newVal) override;
private:
    /*! @brief The Id for the logger */
    const int64_t _loggerID;
    /*! @brief The ID for this thread */
    const int _threadID;
    /*! @brief The amount of time (in micro seconds) between each successive fire */
    const long _fireRatioMicro;
    /*! @brief Threadsafe bool kill handler for the thread */
    const utility::ThreadSafeT<bool>& _killHandler;
    /*! @brief The interface that the test thread will communicate through */
    std::shared_ptr<Communication::I_communication>& _commsInterface;
    /*! @brief The Protocol that we'll be testing */
    std::shared_ptr<Protocol::I_protocolInterface>& _ProtocolInterface;
    /*! @brief Contains results gained from testing */
    safeContainers::safeList<Protocol::DataStruct>& _resultsList;
    /*! @brief Contains a list of all result codes */
    safeContainers::safeList<int>& _codeList;
    /*! @brief tells us if the thread is still running */
    bool _finished;
    /*! @brief mutex used for accessing the _finished member */
    std::mutex _finishedMut;
    /*!
     * @brief dummy function for boost's asynch_wait
     */
     void _dummyFunc();
};
} /* namespace testRunner */
/*! @} */
#endif /* PROTOCOLDEVELOPER_TESTTHREAD_H */

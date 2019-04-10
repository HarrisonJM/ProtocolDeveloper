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
#ifndef PROTOCOLDEVELOPER_I_TESTTHREAD_H
#define PROTOCOLDEVELOPER_I_TESTTHREAD_H

#include <utility/threadSafeT.h>
#include <I_communication.h>
#include <I_protocolInterface.h>
#include <safeList/safeList.h>

namespace testRunner
{
/*!
 * @brief A single test thread
 */
class I_TestThread
{
public:
    /*!
     * @brief Constructor
     */
    I_TestThread() = default;
    /*!
     * @brief Contructor
     * @param killThread_in A reference to the kill thread handler
     * @param commsInterface_in The comms that we are interfacing over
     * @param protocolInterface_in The protocol that we are using to generate data
     * @param resultsList_in Where to store the results
     * @param ratio_in The rough gap between firings we want
     */
    I_TestThread(const utility::ThreadSafeT<bool>& killThread_in
               , std::shared_ptr<Communication::I_communication>& commsInterface_in
               , std::shared_ptr<Protocol::I_protocolInterface>& protocolInterface_in
               , safeContainers::safeList<Protocol::DataStruct>& resultsList_in
               , safeContainers::safeList<int>& codeList_in
               , long ratio_in
               , int64_t loggerID
               , int threadID) {}
    /*!
     * @brief Destructor
     */
    ~I_TestThread() = default;
    /*!
     * @brief Performs the test
     */
    virtual void StartTest() = 0;
    /*!
     * @brief Returns whether or not the thread is finished (threadsafe)
     * @return the internal finished boolean
     */
    virtual bool GetFinished() = 0;
    /*!
     * @brief Sets the internal finished boolean (threadsafe)
     * @param newVal What to set the finished boolean to
     */
    virtual void SetFinished(bool newVal) = 0;
};
} /* namespace CHANGEME */
/*! @} @} */
#endif /* PROTOCOLDEVELOPER_I_TESTTHREAD_H */

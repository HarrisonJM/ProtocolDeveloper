/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup TestRunner
 *
 * @date 16/01/19
 */

#include <boost/asio.hpp>

#include "testThread.h"

namespace TestRunner
{
/*!
 * @brief Contructor
 * @param killThread_in A reference to the kill thread handler
 * @param commsInterface_in The comms that we are interfacing over
 * @param protocolInterface_in The protocol that we are using to generate data
 * @param resultsList_in Where to store the results
 * @param codeList_in Where to store resultant error codes
 * @param ratio_in The rough gap between firings we want
 */
TestThread::TestThread(const Utility::ThreadSafeT<bool>& killThread_in
                       , std::shared_ptr<Communication::I_communication>& commsInterface_in
                       , std::shared_ptr<Protocol::I_protocolInterface>& protocolInterface_in
                       , SafeContainers::safeList<Protocol::DataStruct>& resultsList_in
                       , SafeContainers::safeList<int>& codeList_in
                       , long ratio_in)
    : _fireRatioMicro(ratio_in)
      , _killHandler(killThread_in)
      , _commsInterface(commsInterface_in)
      , _ProtocolInterface(protocolInterface_in)
      , _resultsList(resultsList_in)
      , _codeList(codeList_in)
      , _finished(false)
{
}
/*!
 * @brief Starts the test thread running
 */
void TestThread::StartTest()
{
    /* Setup the threads firing context */
    boost::asio::io_context io;
    boost::asio::steady_timer t(io
                                , boost::asio::chrono::microseconds(_fireRatioMicro));

    while (true)
    {
        t.wait();
        /* Interract with the protocol */
//        auto protData = std::make_shared<Protocol::DataStruct>(); /* Protocol should track state */
        auto protData = _ProtocolInterface->GetDataToSend();
        /* Interact with the target */
        _commsInterface->SendData(protData->_data_p
                                  , protData->_size);
        _commsInterface->ReceiveData(protData->_data_p
                                     , protData->_size);
        /* Process the result */
        _ProtocolInterface->DecodeResult(protData);
        /* Store the result */
        _resultsList.push_back(*protData);
        _codeList.push_back(_ProtocolInterface->GetResultCode());
        /* Check if the thread must die */
        if (_killHandler)
            break;
    }
    _finished = true;
}
/*!
 * @brief Returns whether or not the thread is finished
 * @return the internal finished boolean
 */
bool TestThread::GetFinished()
{
    std::unique_lock<std::mutex> lock(_finishedMut);
    lock.lock();
    return _finished;
}
/*!
 * @brief Sets the internal finished boolean (threadsafe)
 */
void TestThread::SetFinished(bool newVal)
{
    std::unique_lock<std::mutex> lock(_finishedMut);
    lock.lock();

    _finished = newVal;
}
} /* namespace TestRunner */
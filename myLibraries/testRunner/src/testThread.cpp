/*!
 * @brief The individual test thread that will handle sending and sending/receiving data
 * to/FROM the target
 *
 * @author hmarcks
 *
 * @addtogroup TestRunner
 *
 * @date 16/01/19
 */

#include <boost/asio.hpp>
#include <iostream>

#include "testThread.h"
//#include "../../helloWorldProtocol/include/HelloWorldProtocol.h"
#include "libnetworkCommunication/libNetworkCommunication.h"

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
TestThread::TestThread(const utility::ThreadSafeT<bool>& killThread_in
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

    auto _commsInterface2 = new libNetworkCommunication::libNetworkCommunication;
    auto connSucc = _commsInterface2->EstablishConnection();
    int counter = 0;
    while (connSucc)
    {
        t.wait();
        /* Interract with the protocol */
//        auto protData = std::make_shared<Protocol::DataStruct>(); /* Protocol should track state */
//! @TODO: fix this
//        auto _ProtocolInterface2 = new hwProt::HelloWorldProtocol;
//        auto protData = _ProtocolInterface2->GetDataToSend();
        auto protData = _ProtocolInterface->GetDataToSend();
        /* Interact with the target */
        auto foo = protData->_data_p;
        auto bar = protData->_size;

        auto error = _commsInterface2->SendData(foo
                                                , bar);
        if (-1 != error)
        {
            break;
        }
        error = _commsInterface2->ReceiveData(protData->_data_p
                                              , protData->_size);
        if (-1 != error)
        {
            break;
        }
        /* Process the result */
        _ProtocolInterface->DecodeResult(protData);
        /* Store the result */
        _resultsList.push_back(*protData);
        std::cout << counter << std::endl;
//        _codeList.push_back(_ProtocolInterface->GetResultCode());
        /* Check if the thread must die */
        if (_killHandler)
        {
            _commsInterface2->Disconnect();
            break;
        }
        counter++;
    }
    t.wait();
    SetFinished(true);
}
/*!
 * @brief Returns whether or not the thread is finished
 * @return the internal finished boolean
 */
bool TestThread::GetFinished()
{
    std::lock_guard<std::mutex> lock(_finishedMut);
    return _finished;
}
/*!
 * @brief Sets the internal finished boolean (threadsafe)
 */
void TestThread::SetFinished(bool newVal)
{
    std::lock_guard<std::mutex> lock(_finishedMut);
    _finished = newVal;
}
} /* namespace TestRunner */
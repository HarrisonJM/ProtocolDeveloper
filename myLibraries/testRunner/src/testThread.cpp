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
#include <logger/loggerUtility.h>
#include <logger/LogHandler.h>

#include "testThread.h"
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
                       , long ratio_in
                       , int64_t loggerID
                       , int threadID)
    : _loggerID(loggerID)
      , _threadID(threadID)
      , _fireRatioMicro(ratio_in)
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
    boost::asio::steady_timer t(io);
    t.expires_after(boost::asio::chrono::microseconds(_fireRatioMicro));

    auto _commsInterface2 = new libNetworkCommunication::libNetworkCommunication;
    auto connSucc = _commsInterface2->EstablishConnection();
    short error = 0;
    while (connSucc)
    {
        /* Interract with the protocol */
//        auto protData = std::make_shared<Protocol::DataStruct>(); /* Protocol should track state */
//! @TODO: fix this
//        auto _ProtocolInterface2 = new hwProt::HelloWorldProtocol;
//        auto protData = _ProtocolInterface2->GetDataToSend();
        auto protData = _ProtocolInterface->GetDataToSend();
        /* Interact with the target */
        auto foo = protData->_data_p;
        auto bar = protData->_size;

        error = _commsInterface2->SendData(foo
                                           , bar);
        if (-1 == error)
        {
            error = 1;
            break;
        }
        error = _commsInterface2->ReceiveData(protData->_data_p
                                              , protData->_size);
        if (-1 == error)
        {
            error = 2;
            break;
        }
        /* Process the result */
        _ProtocolInterface->DecodeResult(protData);
        std::cout << (char*) (protData->_data_p) << std::endl;
        /* Store the result */
        _resultsList.push_back(*protData);
        std::cout << protData->_data_p << std::endl;
//        _codeList.push_back(_ProtocolInterface->GetResultCode());
        /* Check if the thread must die */
        if (_killHandler)
        {
            LOGMESSAGE("Kill handler invoked"
                       , LoggerClasses::logLevel::INFO);
            break;
        }
        t.async_wait(std::bind(&TestThread::_dummyFunc, this));
        io.run();
        t.expires_after(std::chrono::microseconds(_fireRatioMicro));
    }
    if (connSucc)
    {
        switch (error)
        {
            case 1:
                LOGMESSAGE("Send error"
                           , LoggerClasses::logLevel::INFO);
                break;
            case 2:
                LOGMESSAGE("Receive error"
                           , LoggerClasses::logLevel::INFO);
                break;
            default:
                LOGMESSAGE("Test thread finished"
                           , LoggerClasses::logLevel::INFO);
                break;
        }
        _commsInterface2->Disconnect();
    }
    else
    {
        LOGMESSAGE("Connection failure"
                   , LoggerClasses::logLevel::INFO);
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
void TestThread::_dummyFunc(void)
{
    return;
}
} /* namespace TestRunner */
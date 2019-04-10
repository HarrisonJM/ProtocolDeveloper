/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup NetworkCommunication Library
 * @{
 * @date March 2018
 *
 * @todo perror needs changing to try catch blocks the use strerror
 * @todo refactor out setInterface. Do it in the constructor
 */

#include <iostream>

#include <cstdarg>
#include <freeFunctionsAndWrappers/cStdLib.h>
#include <freeFunctionsAndWrappers/cNetComm.h>

#include "libnetworkCommunication/networkCommunication.h"

namespace networkCommunication
{

bool NetworkCommunication::_alreadyConnected = false;

/*!
 * @brief Constructor
 */
NetworkCommunication::NetworkCommunication()
    :
    _portToSendTo(9687)
      , _destinationAddress("localhost")
      , _outSocket(-1)
      , _tcpOrUDP(1)
      , _servInfo(nullptr)
      , _netCommFunctions(std::make_shared<cFunctions::cNetComm>())
{
}
 /*!
 * @brief Constrcutor, provides an iOInterface set
 * @param iOInterface The iOFunctions we'd like to use (put through an I_cNetComm interface.
 * Only used for testing purposes)
 */
NetworkCommunication::NetworkCommunication(std::shared_ptr<cFunctions::I_cNetComm> iOInterface)
    : _portToSendTo(9687)
      , _destinationAddress("127.0.0.1")
      , _outSocket(-1)
      , _tcpOrUDP(1)
      , _servInfo(nullptr)
      , _netCommFunctions(std::move(iOInterface))
{
}
/*!
 * @brief Returns the plugins name
 * @return The name of the plugin (as a const char*)
 */
const char* NetworkCommunication::getPluginName()
{
    return "NetworkCommunication-def";
}
/*!
 * @brief Returns the version of the plugin
 * @return The plugin version
 */
const char* NetworkCommunication::getPluginVersion()
{
    return "1.0";
}
/*!
 * @brief Returns the plugin _type_
 * @return The the plugin is (as an enum)
 */
pluginLoader::PLUGINTYPE_t NetworkCommunication::getPluginType()
{
    return pluginLoader::PLUGINTYPE_t::COMMUNICATION;
}
/*!
 * @brief Sends the provided data on the socket
 * @param payLoad_p A pointer to the information we want to send
 * @param size The size of the information we want to send
 * @return True on success, otherwise false
 */
ssize_t NetworkCommunication::SendData(void* payLoad_p
                                          , size_t size)
{
    ssize_t numBytes = _netCommFunctions->sendTo(_outSocket
                                                 , payLoad_p
                                                 , size
                                                 , MSG_NOSIGNAL);
    if (-1 == numBytes)
    {
        perror("Send");
    }

    return numBytes;
}
/*!
 * @brief Receives data ready to pass be processed
 * @param payLoad_p A pointer to where to store the data
 * @param size The size of the received data
 * @return None
 */
ssize_t NetworkCommunication::ReceiveData(void* payLoad_p
                                             , size_t size)
{
    ssize_t numBytes = _netCommFunctions->recvFrom(_outSocket
                                                   , payLoad_p
                                                   , size
                                                   , 0);
    if (-1 == numBytes)
    {
        perror("Recv");
    }

    return numBytes;
}
/*!
 * @brief Establishes a connection with the remote
 * @return True on success, otherwise false
 */
bool NetworkCommunication::EstablishConnection()
{
    if (!_alreadyConnected)
        if (SetupAddrInfo())
            if (DoSocketAndConnect())
            {
                _alreadyConnected = true;
                return _alreadyConnected;
            }

    return _alreadyConnected;
}
/*!
 * @brief Disconnects form the remote
 * @return None
 */
void NetworkCommunication::Disconnect()
{
    close(_outSocket);
}
/*!
 * @brief Sets the port we wish to send to
 * @param port The port we wish to send to
 */
void NetworkCommunication::SetPortToSendTo(int port)
{
    _portToSendTo = port;
}
/*!
 * @brief Sets the destination address we wish to send to
 * @param destinationAddress The destionation address we wisht o send to
 */
void NetworkCommunication::SetDestinationAddress(char* destinationAddress)
{
    _destinationAddress = destinationAddress;
}
/*!
 * @brief Sets whether we are a TCP or UDP connection
 * @param tcpOrUDP 1 for TCP 0 for UDP
 */
void NetworkCommunication::SetTCPOrUDP(int tcpOrUDP)
{
    _tcpOrUDP = tcpOrUDP;
}
/*!
 * @brief Sets additional server info with the addrinfo struct
 * @param _servinfo The additional server info
 */
void NetworkCommunication::SetServInfo(addrinfo* _servinfo)
{
    _servInfo = _servinfo;
}
/*!
 * @brief Sets the interface we'll be using to communicate with
 * @param iOInterface A shared_ptr to the interface we'll be using
 *
 * @return None
 */
void NetworkCommunication::SetInterface(std::shared_ptr<cFunctions::I_cNetComm> iOInterface)
{
    _netCommFunctions = iOInterface;
}
/*!
 * @brief setups up the ProtDev connection/client Information
 * @return None
 */
bool NetworkCommunication::SetupAddrInfo()
{
    addrinfo hints = {0};
    addrinfo* addrsGotten;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = _tcpOrUDP ? SOCK_STREAM : SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // Do *my* IP for me

    int status = 0;
    status = _netCommFunctions->getaddressinfo(_destinationAddress.c_str()
                                               , std::to_string(_portToSendTo).c_str()
                                               , &hints
                                               , &addrsGotten);
    /*!
     * @todo Change when using [out] values worked out
     * See related tests for this class
     */
    if (0 != status)
        if (nullptr == _servInfo)
        {
            //! @todo exception handling
            fprintf(stderr
                    , "getaddr failure in SetupAddrInfo():#%d: %s"
                    , __LINE__
                    , gai_strerror(status));
            return false;
        }

    _servInfo = addrsGotten;

    return true;
}
/*!
 * @brief sets up the socket and connects to the remote
 * @return None
 */
bool NetworkCommunication::DoSocketAndConnect()
{
    addrinfo* p;

    // Loop through all the results and bind to each

    for (p = _servInfo; nullptr != p; p = p->ai_next)
    {
        _outSocket = _netCommFunctions->createSocket(p->ai_family
                                                     , p->ai_socktype
                                                     , p->ai_protocol);
        if (-1 == _outSocket)
        {
            perror("client socket");
            continue;
        }

        if (-1 == _netCommFunctions->connectToRemote(_outSocket
                                                     , p->ai_addr
                                                     , p->ai_addrlen))
        {
            _netCommFunctions->closeConnection(_outSocket);
            perror("client connect");
            continue;
        }
        break;
    }

    if (nullptr == p)
    {
        //! @todo exception handling
        fprintf(stderr
                , "Could not connect to remote\n");
        return false;
    }

    _netCommFunctions->freeaddressinfo(_servInfo);

    return true;
}

} /* namespace NetworkCommunication */
/*! @} */

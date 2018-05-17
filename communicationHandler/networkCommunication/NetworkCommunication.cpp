/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup NetworkCommunication
 *
 * @date March 2018
 *
 * @todo perror needs changing to try catch blocks the use strerror
 */
#include <iostream>
#include "NetworkCommunication.h"
#include "cStdLib.h"

namespace Communication
{
/*!
 * @brief Constructor
 */
NetworkCommunication::NetworkCommunication()
    : _portToSendOn(9687),
      _destinationAddress("localhost"),
      _outSocket(-1),
      _tcpOrUDP(1),
      _servInfo(nullptr),
      _netCommFunctions(nullptr)
{

}

/*!
 * @brief destructor
 */
NetworkCommunication::~NetworkCommunication()
{

}

/*!
 * @brief Sends the provided data on the socket
 *
 * @param payLoad_p A pointer to the information we want to send
 * @param size The size of the information we want to send
 * @return True on success, otherwise false
 */
ssize_t NetworkCommunication::SendData(void *payLoad_p,
                                       size_t size)
{
    ssize_t numBytes = _netCommFunctions->sendPacket(_outSocket,
                                                    payLoad_p,
                                                    size,
                                                    0);
    if (-1 == numBytes)
    {
        perror("Send");
    }

    return numBytes;
}

/*!
 * @brief Receives data ready to pass be processed
 *
 * @param payLoad_p A pointer to where to store the data
 * @param size The size of the received data
 *
 * @return None
 */
ssize_t NetworkCommunication::ReceiveData(void *payLoad_p,
                                          size_t size)
{
    ssize_t numBytes = _netCommFunctions->recvPacket(_outSocket,
                                                    payLoad_p,
                                                    size,
                                                    0);
    if (-1 == numBytes)
    {
        perror("Recv");
    }

    return numBytes;
}

/*!
 * @brief establishes a connection with the remote
 *
 * @return True on success, otherwise false
 */
bool NetworkCommunication::EstablishConnection()
{
    if(SetupAddrInfo())
        if(DoSocketAndConnect())
            return true;

    return false;
}

/*!
 * @brief Disconnects form the remote
 *
 * @return None
 */
void NetworkCommunication::Disconnect()
{
    close(_outSocket);
}

/*!
 * @brief Sets the interface we'll be using to communicate with
 * (sockets, files, pipes, etc)

 * @param iOInterface A pointer to the interface we'll be using
 *
 * @return None
 */
void NetworkCommunication::setInterface(cFunctions::I_cNetComm* iOInterface)
{
    _netCommFunctions = iOInterface;
}

/*!
 * @brief setups up the ProtDev connection/client Information
 *
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
    status = _netCommFunctions->getAddrInfo(_destinationAddress.c_str(),
                                           std::to_string(_portToSendOn)
                                               .c_str(),
                                           &hints,
                                           &addrsGotten);

    /*!
     * @todo Change when using [out] values worked out
     * See related tests for this class
     */
    if (0 != status)
        if (NULL == _servInfo)
        {
            //! @todo exception handling
            fprintf(stderr,
                    "getaddr failure in SetupAddrInfo():#%d: %s",
                    __LINE__,
                    gai_strerror(status));
            return false;
        }

    _servInfo = addrsGotten;

    return true;
}

/*!
 * @brief sets up the socket and connects to the remote
 *
 * @return None
 */
bool NetworkCommunication::DoSocketAndConnect()
{
    addrinfo *p;

    // loop through all the results and bind to each

    for (p = _servInfo; nullptr != p; p = p->ai_next)
    {
        _outSocket = _netCommFunctions->createSocket(p->ai_family,
                                                    p->ai_socktype,
                                                    p->ai_protocol);
        if (-1 == _outSocket)
        {
            perror("client socket");
            continue;
        }

        if (-1 == _netCommFunctions->connectToRemote(_outSocket,
                                                    p->ai_addr,
                                                    p->ai_addrlen))
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
        fprintf(stderr,
                "Could not connect to remote\n");
        return false;
    }

    _netCommFunctions->freeAddrInfo(_servInfo);

    return true;
}

} /* namepsace communication */
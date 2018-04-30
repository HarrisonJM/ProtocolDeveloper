/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup NetworkCommunication
 *
 * @date March 2018
 */
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

#include "NetworkCommunication.h"

namespace Communication
{
    /*!
     * @brief Constructor
     */
    NetworkCommunication::NetworkCommunication()
        : portToBind("65000"),
          portToSend("9687"),
          address("localhost"),
          outSocket(-1),
          tcpOrUDP(1)
    {

    }

    /*!
     * @brief Destructor
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
    bool NetworkCommunication::SendData(void *payLoad_p, int size)
    {
        std::cout << "Sending data" << std::endl;
        const char* blah = "hello";
        send(outSocket, (void*)blah, 6, 0);

        return true;
    }

    /*!
     * @brief Receives data ready to pass be processed
     *
     * @param payLoad_p A pointer to where to store the data
     * @param size The size of the received data
     *
     * @return None
     */
    void NetworkCommunication::ReceiveData(void *payLoad_p, int size)
    {
        recv(outSocket, (void*)msg, 20, 0);
    }

    /*!
     * @brief establishes a connection with the remote
     *
     * @return True on success, otherwise false
     */
    bool NetworkCommunication::EstablishConnection()
    {
        addrinfo *servinfo = nullptr;

        SetupAddrInfo(servinfo);
        DoSocketAndConnect(servinfo);
        return true;
    }

    /*!
     * @brief Disconnects form the remote
     *
     * @return None
     */
    void NetworkCommunication::Disconnect()
    {

    }

    /*!
     * @brief setups up the ProtDev connection/client Information
     *
     * @return none
     */
    void NetworkCommunication::SetupAddrInfo(addrinfo *servinfo)
    {
        int status = 0;
        addrinfo hints = {0};

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC; // Either ipv4 or 6
        hints.ai_socktype = SOCK_STREAM; //tcp
        hints.ai_flags = AI_PASSIVE; // Do *my* IP for me

        if (0 != (status = getaddrinfo(address.c_str(), portToBind.c_str(), &hints, &servinfo)))
        {
            fprintf(stderr, "getaddr failure in SetupAddrInfo(): %s" , gai_strerror(status));
            exit(1);
        }
    }

    /*!
     * @brief sets up the socket and connects to the remote
     *
     * @todo Needs to work on datagram too
     *
     * @return None
     */
    void NetworkCommunication::DoSocketAndConnect(addrinfo *servinfo)
    {
        addrinfo *p;
        // loop through all the results and bind to each
        for(p = servinfo; p != nullptr; p = p->ai_next)
        {
            if (-1 == (outSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)))
            {
                perror("server: socket");
                continue;
            }

            if (-1 == connect(outSocket, p->ai_addr, p->ai_addrlen))
            {
                close(outSocket);
                perror("client: connect");
                continue;
            }
        }
    }
    std::string NetworkCommunication::getMsg()
    {
        return std::string(msg);
    }
}
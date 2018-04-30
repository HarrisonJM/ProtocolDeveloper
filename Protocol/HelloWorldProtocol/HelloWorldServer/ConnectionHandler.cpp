/*!
 * @brief Handles incoming and outgoing connections
 *
 * @addtogroup HelloGoodByeServer
 *
 * @date March 2018
 */
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>

#include "BasicHello.h"
#include "ConnectionHandler.h"

namespace BasicHelloServer
{
    /*!
     * @brief Basic constructor
     *
     * @param server A reference to the server information
     */
    ConnectionHandler::ConnectionHandler(ServerSetup &server)
        : server(server)
    {
        auto *BH = new BasicHello();
        cfg = BH;
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Accepts incoming client connections
     *
     * Forks off extra client connections
     *
     * @return None
     */
    void ConnectionHandler::AcceptNewConnections()
    {
        struct sockaddr_storage addr = {0};
        socklen_t addrlen = sizeof(addr);
        std::cout << "Awaiting new connection" << std::endl;
        int clientSockFD = accept(server.getSockFD(), (struct sockaddr *) &addr, &addrlen);
        std::cout << "New connection!" << std::endl;

        if (-1 == clientSockFD)
            perror("accept");
        else if (!fork())
            HandleRequest(clientSockFD);

        if (-1 != clientSockFD)
            close(clientSockFD);
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Deals with requests
     *
     * @param fd The Socket File Descriptor
     *
     * @return None
     */
    void ConnectionHandler::HandleRequest(int fd)
    {
        void *payLoad = nullptr;
        payLoad = malloc(7);
        recv(fd, payLoad, 7, 0);

        cfg->receiveData(payLoad);

        send(fd, cfg->sendData(), 7, 0);
        free(payLoad);
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Destructor
     */
    ConnectionHandler::~ConnectionHandler()
    {
        auto iter = sessions.rbegin();
        for (; iter != sessions.rend(); ++iter)
        {
            close(*iter);
            sessions.pop_back();
        }

        delete (&server);
        delete(cfg);
    }
}
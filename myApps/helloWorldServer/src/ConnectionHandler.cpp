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
        : _server(server)
    {
        auto *BH = new BasicHello();
        _cfg = BH;
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
        int clientSockFD = accept(_server.getSockFD(), (struct sockaddr *) &addr, &addrlen);
        std::cout << "New connection!" << std::endl;

        if (-1 == clientSockFD)
            perror("accept");
        else if (!fork())
            _HandleRequest(clientSockFD);

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
    void ConnectionHandler::_HandleRequest(int fd)
    {
        void *payLoad = nullptr;
        payLoad = malloc(7);
        recv(fd, payLoad, 7, 0);

        _cfg->receiveData(payLoad);

        send(fd, _cfg->sendData(), 7, 0);
        free(payLoad);
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Destructor
     */
    ConnectionHandler::~ConnectionHandler()
    {
        auto iter = _sessions.rbegin();
        for (; iter != _sessions.rend(); ++iter)
        {
            close(*iter);
            _sessions.pop_back();
        }

        delete (&_server);
        delete(_cfg);
    }
}
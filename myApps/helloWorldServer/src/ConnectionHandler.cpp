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
ConnectionHandler::ConnectionHandler(ServerSetup& server)
    : _server(server)
{
    auto* BH = new BasicHello();
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
    int clientSockFD = accept(_server.getSockFD()
                              , (struct sockaddr*) &addr
                              , &addrlen);
    std::cout << "New connection!" << std::endl;

    static int num = 0;
    if (-1 == clientSockFD)
        perror("accept");
    else if (!fork())
    {
        num++;
        _HandleRequest(clientSockFD
                       , 0);
        num--;
    }

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
void ConnectionHandler::_HandleRequest(int fd
                                       , int ID)
{
    int counter = 0;
    void* payLoad = nullptr;
    payLoad = malloc(30);
    while (counter < 100)
    {
        recv(fd
             , payLoad
             , 30
             , 0);
        _cfg->receiveData(payLoad);
        std::cout << (char*) payLoad << std::endl;
        send(fd
             , _cfg->sendData()
             , 30
             , 0);
        counter++;
    }
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
    delete (_cfg);
}
}
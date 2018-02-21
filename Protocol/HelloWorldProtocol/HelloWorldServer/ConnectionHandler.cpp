#include <unistd.h>
#include <iostream>

#include "BasicHello.h"
#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(ServerSetup &server)
: server(server)
{
    auto *BH = new BasicHello();
    cfg = (ConfigurationInterface*)BH;
}

//-----------------------------------------------------------------------------

void ConnectionHandler::AcceptNewConnections()
{
    struct sockaddr_storage addr = {0};
    socklen_t addrlen = sizeof(addr);
    //sessions.push_back(accept(server.getSockFD(), &addr, &addrlen));
    std::cout << server.getSockFD() << std::endl;
    int clientSockFD = accept(server.getSockFD(), (struct sockaddr *)&addr, &addrlen);
    std::cout << clientSockFD << std::endl;
    HandleRequest(clientSockFD);
}

//-----------------------------------------------------------------------------

void ConnectionHandler::HandleRequest(int fd)
{
    void* payLoad = nullptr;
    payLoad = malloc(7);
    recv(fd, payLoad, 7, 0);

    cfg->receiveData(payLoad);

    send(fd, cfg->sendData(), 7, 0);
}

//-----------------------------------------------------------------------------

ConnectionHandler::~ConnectionHandler()
{
    auto iter = sessions.rbegin();
    for(; iter != sessions.rend(); ++iter)
    {
        close(*iter);
        sessions.pop_back();
    }

    delete(&server);
}

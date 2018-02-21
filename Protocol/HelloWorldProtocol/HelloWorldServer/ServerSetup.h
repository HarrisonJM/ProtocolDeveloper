#ifndef PROTOCOLDEVELOPER_SERVERSETUP_H
#define PROTOCOLDEVELOPER_SERVERSETUP_H

#include <netdb.h>
#include <string>

#define MAX_CONNECTIONS 5
typedef struct addrinfo addrinfo;

// This class will exist as "the server" and listen on the provided port

class ServerSetup
{
public:
    explicit ServerSetup(std::string portToUse);
    ~ServerSetup();

    int getSockFD();
private:
    /* METHODS */
    void setupAddrInfo();
    void doSocketAndBind();
    void doListen();

    /* Not Methods */
    addrinfo *servinfo;
    int sockfd;
    std::string port;
};

#endif //PROTOCOLDEVELOPER_SERVERSETUP_H
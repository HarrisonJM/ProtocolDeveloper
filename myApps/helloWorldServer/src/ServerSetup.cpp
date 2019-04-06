/*!
 * @brief Sets up the server
 *
 *  @addtogroup HelloGoodByeServer
 *
 *  @date March 2018
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <netdb.h>

#include "ServerSetup.h"
namespace BasicHelloServer
{
    /*!
     * @brief Default Constructor
     *
     * @param portToUse The number of the port to use for communication
     */
    ServerSetup::ServerSetup(std::string portToUse)
        : _port(std::move(portToUse))
    {
        _servInfo = (addrinfo *) malloc(sizeof(addrinfo));
        memset(&_servInfo, 0, sizeof _servInfo);
        // constructor for our _server class
        // Get information for the bind
        setupAddrInfo();
        doSocketAndBind();
        doListen();
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Destructor
     */
    ServerSetup::~ServerSetup()
    {
        // clean up. Unbind from socket, etc
        if (_sockfd != -1)
            close(_sockfd);
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Sets up The Address Server Info
     *
     * @return None
     */
    void ServerSetup::setupAddrInfo()
    {
        int status = 0;
        addrinfo hints = {0};

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC; // Either ipv4 or 6
        hints.ai_socktype = SOCK_STREAM; //tcp
        hints.ai_flags = AI_PASSIVE; // Do my IP for me

        if (0 != (status = getaddrinfo("localhost", _port.c_str(), &hints, &_servInfo)))
        {
            fprintf(stderr, "getaddr failure in SetupAddrInfo(): %s", gai_strerror(status));
            exit(1);
        }
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief performs the bind and removes warning about port number
     *
     * @return None
     */
    void ServerSetup::doSocketAndBind()
    {
        int yes = 1;
        addrinfo *p;
        // loop through all the results and bind to the first we can
        for (p = _servInfo; p != nullptr; p = p->ai_next)
        {
            _sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (-1 == _sockfd)
            {
                perror("_server: socket");
                continue;
            }

            if (-1 == setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)))
            {
                perror("setsockopt");
                exit(1);
            }

            const int ret = bind(_sockfd, p->ai_addr, p->ai_addrlen);
            if (-1 == ret)
            {
                close(_sockfd);
                perror("_server: bind");
                continue;
            }

            break;
        }

        freeaddrinfo(_servInfo); // all done with this structure
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Do the listen
     *
     * @return None
     */
    void ServerSetup::doListen()
    {
        std::cout << _sockfd << std::endl;

        if (-1 == listen(_sockfd, MAX_CONNECTIONS))
        {
            perror("listen");
            exit(1);
        }
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Returns the Socket FD
     *
     * @return The Socekt FD
     */
    int ServerSetup::getSockFD()
    {
        return _sockfd;
    }
}
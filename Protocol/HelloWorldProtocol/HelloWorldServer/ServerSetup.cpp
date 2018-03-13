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
        : port(portToUse)
    {
        servinfo = (addrinfo *) malloc(sizeof(addrinfo));
        memset(&servinfo, 0, sizeof servinfo);
        // constructor for our server class
        // Get information for the bind
        setupAddrInfo();
        doSocketAndBind();
        doListen();
    };

//-----------------------------------------------------------------------------

    /*!
     * @brief Destructor
     */
    ServerSetup::~ServerSetup()
    {
        // clean up. Unbind from socket, etc
        if (sockfd != -1)
            close(sockfd);
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
        // p
        hints.ai_flags = AI_PASSIVE; // Do my IP for me

        if (0 != (status = getaddrinfo("localhost", port.c_str(), &hints, &servinfo)))
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
        for (p = servinfo; p != nullptr; p = p->ai_next)
        {
            if (-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)))
            {
                perror("server: socket");
                continue;
            }

            if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)))
            {
                perror("setsockopt");
                exit(1);
            }

            const int ret = bind(sockfd, p->ai_addr, p->ai_addrlen);
            if (-1 == ret)
            {
                close(sockfd);
                perror("server: bind");
                continue;
            }

            break;
        }
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Do the listen
     *
     * @return None
     */
    void ServerSetup::doListen()
    {
        std::cout << sockfd << std::endl;

        if (-1 == listen(sockfd, MAX_CONNECTIONS))
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
        return sockfd;
    }
}
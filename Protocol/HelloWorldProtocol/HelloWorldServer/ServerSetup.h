/*!
 * @brief Sets up the server
 *
 * @addtogroup HelloGoodByeServer
 *
 * @date March 2018
 */
#ifndef PROTOCOLDEVELOPER_SERVERSETUP_H
#define PROTOCOLDEVELOPER_SERVERSETUP_H

#include <string>

#define MAX_CONNECTIONS 5
typedef struct addrinfo addrinfo;

// This class will exist as "the server" and listen on the provided port
namespace BasicHelloServer
{
    class ServerSetup
    {
    public:
        //! Constructor
        explicit ServerSetup(std::string portToUse);
        //! Destructor
        ~ServerSetup();

        //! Returns the socket FD
        int getSockFD();
    private:
        /* METHODS */
        //! Sets up the address info
        void setupAddrInfo();
        //! Creates the socket and binds to it
        void doSocketAndBind();
        //! Listens for connections
        void doListen();

        /* Not Methods */
        //! Stores the servers personal information
        addrinfo *servinfo;
        //! The FD for the server
        int sockfd;
        //! The port we're listening on
        std::string port;
    };
}
#endif //PROTOCOLDEVELOPER_SERVERSETUP_H
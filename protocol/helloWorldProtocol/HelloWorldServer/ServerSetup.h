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

// This class will exist as "the _server" and listen on the provided _port
namespace BasicHelloServer
{
    /*!
     * @brief server setup class
     *
     * Using a port number, sets up a server and begins listening
     */
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
        addrinfo *_servInfo;
        //! The FD for the server
        int _sockfd;
        //! The port we're listening on
        std::string _port;
    };
}
#endif //PROTOCOLDEVELOPER_SERVERSETUP_H
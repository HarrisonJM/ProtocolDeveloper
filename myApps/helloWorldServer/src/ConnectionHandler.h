/*!
 * @brief Handles incoming and outgoing connections
 *
 * @addtogroup HelloGoodByeServer
 *
 * @date March 2018
 */
#ifndef PROTOCOLDEVELOPER_CONNECTIONHANDLER_H
#define PROTOCOLDEVELOPER_CONNECTIONHANDLER_H

#include <vector>
#include "ConfigurationInterface.h"

#include "ServerSetup.h"

/* This will handle connections coming in and going out from the _server.
 * This can be extended to receive an extra parameter that can then produce the required
 * data handler
*/

 /*
  * Currently unused. Will be used to switch on when deciding what configurations to use
  */
typedef enum configuration_t
{
    BASIC
} configuration;

namespace BasicHelloServer
{
    /*!
     * @brief Handles incoming connections
     *
     *  Passes information to where it might be required
     */
    class ConnectionHandler
    {
    public:
        //! Constructor
        explicit ConnectionHandler(ServerSetup &server);
        //! Destructor
        ~ConnectionHandler();

        //! Accepts new connections
        void AcceptNewConnections();

    private:
        /* METHODS */
        //! Handles incoming requests and sends the data to wherever it needs to go
        void _HandleRequest(int fd
                            , int ID);

        /* Not Methods */
        //! Reference to the server
        ServerSetup &_server;
        //! An interface to the configuration we're using
        ConfigurationInterface *_cfg;
        //! A list of all currently active sessions on this handler
        std::vector<int> _sessions;
    };
}

#endif //PROTOCOLDEVELOPER_CONNECTIONHANDLER_H

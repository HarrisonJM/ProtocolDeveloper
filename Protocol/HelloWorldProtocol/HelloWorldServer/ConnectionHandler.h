#ifndef PROTOCOLDEVELOPER_CONNECTIONHANDLER_H
#define PROTOCOLDEVELOPER_CONNECTIONHANDLER_H

#include <vector>
#include "ConfigurationInterface.h"

#include "ServerSetup.h"

/* This will handle connections coming in and going out from the server.
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

class ConnectionHandler
{
public:
    explicit ConnectionHandler(ServerSetup &server);
    ~ConnectionHandler();

    void AcceptNewConnections();

private:
    /* METHODS */
    void HandleRequest(int fd);

    /* Not Methods */
    ServerSetup &server;
    ConfigurationInterface *cfg;
    std::vector<int> sessions;
};


#endif //PROTOCOLDEVELOPER_CONNECTIONHANDLER_H

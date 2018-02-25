#include <csignal>
#include <cstdlib>
#include <thread>

#include "ServerSetup.h"
#include "ConnectionHandler.h"

/*
 * A simple Hello World server. Will send Hello/goodbye world depending on what it receives.
 * Will be used to help develop and test different features of the prot dev program
 *
 * Listen function that will listen for connections, spawn a thread when a connection is made
 * A function that sends information back away and then dies
 * Might be worth implementing a simple killServer command
 */

/*
 * INFORMATION: PORT: 3490
 */
ConnectionHandler *CH;
bool killServer = false;

//-----------------------------------------------------------------------------

void intHandler(int dummy)
{
    killServer = true;
    delete(CH);
}

//-----------------------------------------------------------------------------

int main(int argv, char** argc)
{
    // Get our intHandler out of the way right now. This way we can
    signal(SIGINT, intHandler);

    // We now have a server listening on port 3940 for a connection
    ServerSetup *server = new ServerSetup("9687");
    CH = new ConnectionHandler(*server);
    //TODO: Allow multiple connections with std::thread
    while(killServer == false)
    {
        CH->AcceptNewConnections();
    }
}


/*!
 * @brief Entry point for the hello goodbye server
 *
 * The HelloGoodbye server will deal in and serve the purposes of testing the ProtDev
 * The protocol is defined as sending Hello or goodbye (dependent on receiving the opposite response)
 * in a variety of interpretable ways.
 *
 * A simple Hello World server. Will send Hello/goodbye world depending on what it receives.
 * Will be used to help develop and test different features of the prot dev program
 *
 * Listen function that will listen for connections, spawn a thread when a connection is made
 * A function that sends information back away and then dies
 * Might be worth implementing a simple killServer command
 *
 * @addtogroup HelloGoodByeServer
 *
 * @date March 2018
 */
#include <csignal>
#include <cstdlib>
#include <thread>

#include "ServerSetup.h"
#include "ConnectionHandler.h"

/*
 * INFORMATION: PORT: 9687
 */
BasicHelloServer::ConnectionHandler *CH;
BasicHelloServer::ServerSetup *server;
bool killServer = false;

//-----------------------------------------------------------------------------

/*!
 * @brief SIGINT Handler
 *
 * Handles a SIGINT
 *
 * @param dummy I don't know what this does
 *
 * @return None
 */
void intHandler(int dummy)
{
    killServer = true;
    delete(CH);
    delete(server);
    exit(0);
}

//-----------------------------------------------------------------------------

/*!
 * @brief Entry point for server
 *
 * @param argc The number of arguments passed in
 *
 * @param argv The arguments
 *
 * @return non-zero on error
 */
int main(int argc, char** argv)
{
    // Get our intHandler out of the way right now. This way we can free up the ports immediately
    signal(SIGINT, intHandler);

    // We now have a server listening on port 9687 for a connection
    server = new BasicHelloServer::ServerSetup("9687");
    CH = new BasicHelloServer::ConnectionHandler(*server);
    while(killServer == false)
    {
        CH->AcceptNewConnections();
    }
}


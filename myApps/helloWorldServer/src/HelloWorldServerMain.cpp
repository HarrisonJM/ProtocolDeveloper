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
 * @todo Increase complexity for more tests
 * @todo Add more configurations
 * @todo Reap children (The harvest is small)
 * @todo Tidy up (remove singletons and probably more)
 *
 * @date March 2018
 */
#include <csignal>
#include <cstdlib>
#include <thread>
#include <iostream>

#include "ServerSetup.h"
#include "ConnectionHandler.h"

/*
 * INFORMATION: PORT: 9687
 */
BasicHelloServer::ServerSetup server("9687");
BasicHelloServer::ConnectionHandler CH(server);
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
    //delete(&CH);
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
    // Everything totals itself when its called. I clearly do not understand these things
    //signal(SIGINT, intHandler);

    // We now have a _server listening on _port 9687 for a connection
    std::cout<< "Entering Loop" << std::endl;
    while(killServer == false)
    {
        CH.AcceptNewConnections();
    }
}


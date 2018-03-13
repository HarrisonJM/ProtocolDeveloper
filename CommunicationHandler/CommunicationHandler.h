/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup CommunicationHandler
 *
 * @date March 2018
 */
#include "CommunicationInterface.h"
#include <string>
#include <vector>

#ifndef PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H
#define PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H

//! The max number of connections we want to deal with
#define MAX_CONNECTIONS 5
//! Simple typedef
typedef struct addrinfo addrinfo;

namespace CommunicationHandler
{
    /*!
     * @brief The CommunicationHandler class
     */
    class CommunicationHandler : public CommunicationInterface
    {
    public:
        //! Constructor
        CommunicationHandler();
        //! Destructor
        ~CommunicationHandler();
        // Options will be defined by the user as some sort struct that can be easily cast
        // to and from the required data form. Payload will contain all required information.
        //! Sends Data
        bool SendData(void *payLoad_p, int size) override;
        //! Receives Data
        void ReceiveData(void *payLoad_p, int size) override;
        //! establishes a connection with the remote
        bool EstablishConnection() override;
        //! Disconnects from the Remote
        void Disconnect() override;
    private:
        //! The port we're conducting business on
        std::string port;
        //! The Address we're sending to
        std::string address;
        //! The socket used to bind
        int outSocket;
        //! Socket FDs that are related to outgoing traffic
        std::vector<int> sockets;
        //! The information for this client
        addrinfo *servinfo;
        /* METHODS */
        //! Setups up the addrinfo struct
        void SetupAddrInfo();
        //! Creates the socket and connects
        void DoSocketAndConnect();

    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H

/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup NetworkCommunication
 *
 * @date March 2018
 */
#include "CommunicationInterface.h"

#include <string>
#include <vector>

#ifndef PROTOCOLDEVELOPER_NETWORKCOMMUNICATION_H
#define PROTOCOLDEVELOPER_NETWORKCOMMUNICATION_H

namespace Communication
{
    //! The max number of connections we want to deal with
    static const int MAX_CONNECTIONS = 5;
    //! Simple typedef
    typedef struct addrinfo addrinfo;

    /*!
     * @brief The NetworkCommunication class
     */
    class NetworkCommunication : public CommunicationInterface
    {
    public:
        //! Constructor
        NetworkCommunication();
        //! Destructor
        ~NetworkCommunication();
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

        std::string getMsg();
    private:
        //! The port we're conducting business on
        std::string portToBind;
        //! Port we're sending to
        std::string portToSend;
        //! The Address we're sending to
        std::string address;
        //! The socket used to bind and send on
        int outSocket;
        //! The socket used to receive on
        int inSocket;
        //! Do we want to connect on TCP, UDP, or both?
        int tcpOrUDP:2;

        char *msg;

        /* METHODS */
        //! Setups up the addrinfo struct
        void SetupAddrInfo(addrinfo *servinfo);
        //! Creates the socket and connects
        void DoSocketAndConnect(addrinfo *servinfo);

    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H

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
#include <string>
#include <vector>
#include <memory>

#include "interfaces/I_communication.h"
#include "cNetComm.h"

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
    class NetworkCommunication : public I_communication
    {
    public:
        //! Constructor
        NetworkCommunication();
        //! Destructor
        virtual ~NetworkCommunication();
        //! Sends Data
        ssize_t SendData(void *payLoad_p, size_t size) override;
        //! Receives Data
        ssize_t ReceiveData(void *payLoad_p, size_t size) override;
        //! establishes a connection with the remote
        bool EstablishConnection() override;
        //! Disconnects from the Remote
        void Disconnect() override;
        //! The Interface we want to connect over
        void setInterface(cFunctions::I_cNetComm* iOInterface) override;
    private:
        //! The port we're conducting business on
        int _portToSendOn;
        //! The Address we're sending to
        std::string _destinationAddress;
        //! The socket used to bind and send on
        int _outSocket;
        //! Do we want to connect on TCP, UDP, or both?
        int _tcpOrUDP:2;
        //! The info of the server we're connecting  to
        addrinfo *_servInfo;

        //! Wrapper class for using C socket functions
        cFunctions::I_cNetComm* _netCommFunctions;


        /* METHODS */
        //! Setups up the addrinfo struct
        bool SetupAddrInfo();
        //! Creates the socket and connects
        bool DoSocketAndConnect();
        //! Takes aaddrinfo

    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H

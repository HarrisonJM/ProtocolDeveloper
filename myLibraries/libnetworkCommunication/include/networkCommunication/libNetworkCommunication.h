/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup NetworkCommunication Library
 *
 * @date March 2018
 */
#include <string>
#include <vector>
#include <memory>

#include "I_communication.h"
#include "freeFunctionsAndWrappers/cNetComm.h"

#ifndef PROTOCOLDEVELOPER_NETWORKCOMMUNICATION_H
#define PROTOCOLDEVELOPER_NETWORKCOMMUNICATION_H

namespace libNetworkCommunication
{
//! The max number of connections we want to deal with
static const int MAX_CONNECTIONS = 5;
//! Simple typedef
typedef struct addrinfo addrinfo;
/*!
 * @brief The NetworkCommunication class
 */
class libNetworkCommunication
    : public Communication::I_communication
{
public:
    //! Default Constructor
    libNetworkCommunication();
    /*!
     * @brief Contructor, mainly used for testing
     * @param iOInterface Sets the interface we want to use
     */
    explicit libNetworkCommunication(std::shared_ptr<cFunctions::I_cNetComm> iOInterface);
    //! Destructor
    ~libNetworkCommunication() = default;
    /*!
     * @brief Sends data
     * @param payLoad_p The data we wish to send
     * @param size The size of the data
     * @return The size of the data sent
     */
    ssize_t SendData(void* payLoad_p
                     , size_t size) override;
    /*!
     * @brief Recevies Data
     * @param payLoad_p Where to store the data we've recevied
     * @param size The size of the payload buffer
     * @return The size of the data received
     */
    ssize_t ReceiveData(void* payLoad_p
                        , size_t size) override;
    /*!
     * @brief Establishes a connection with the remote
     * @return true for success, otherwise false
     */
    bool EstablishConnection() override;
    /*!
     * @brief Disconnects from the target
     */
    void Disconnect() override;

    /*!
     * @brief Sets the port we wish to send on
     * @param port The port we wish to send on
     */
    void setPortToSendTo(int port);
    /*!
     * @brief Set the destination's address
     * @param destinationAddress The address we wish to send to
     */
    void setDestinationAddress(char* destinationAddress);
    /*!
     * @brief Set whether TCP or UDP
     * @param tcpOrUDP 1 for TCP, 0 for UDP
     */
    void setTCPOrUDP(int tcpOrUDP);
    /*!
     * @brief Supply extra information for connecting to a server
     * @param _servinfo A pointer to the address info we wish to use
     */
    void setServInfo(addrinfo* _servinfo);
    /*!
     * @brief The Interface we want to connect over
     * @param iOInterface A shared_ptr containing the concrete implementation we wish to use
     */
    void setInterface(std::shared_ptr<cFunctions::I_cNetComm> iOInterface);
    /*!
     * @brief Returns the plugins name
     * @return The name of the plugin (as a const char*)
     */
    const char* getPluginName() override;
    /*!
     * @brief Returns the version of the plugin
     * @return The plugin version
     */
    const char* getPluginVersion() override;
    /*!
     * @brief Returns the plugin _type_
     * @return The the plugin is (as an enum)
     */
    PluginLoader::PLUGINTYPE_t getPluginType() override;
    /*!
     * @brief creates a new NetworkCommuncation object and returns its address
     * @return A pointer to the new Communication object with it's default parameters
     */
    static boost::shared_ptr<Communication::I_communication> createObject();
private:
    /*! The port we're conducting business on */
    int _portToSendTo;
    /*! The Address we're sending to */
    char* _destinationAddress;
    /*! The socket used to bind and send on */
    int _outSocket;
    /*! Do we want to connect on TCP, UDP, or both? */
    int _tcpOrUDP;
    /*! The info of the server we're connecting  to */
    addrinfo* _servInfo;
    /*! Wrapper class for using C socket functions */
    std::shared_ptr<cFunctions::I_cNetComm> _netCommFunctions;

    /*!
     * @brief Setups up the addrinfo struct
     * @return true for success, otherwise false
     */
    bool SetupAddrInfo();
    /*!
     * @brief Creates the socket and connects
     * @return true for success, otherwise false
     */
    bool DoSocketAndConnect();
};
} /* namespace libNetworkCommunication */

#endif //PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H

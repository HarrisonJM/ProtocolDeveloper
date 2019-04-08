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
#include <mutex>
#include "freeFunctionsAndWrappers/cNetComm.h"

#include <I_libNetworkCommunication.h>

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
    : public I_libNetworkCommunication
{
public:
    /*!
     * @brief Default Constructor
     */
    libNetworkCommunication();
    /*!
     * @brief Contructor, mainly used for testing
     * @param iOInterface Sets the interface we want to use
     */
    explicit libNetworkCommunication(std::shared_ptr<cFunctions::I_cNetComm> iOInterface);
    /*!
     * @brief Default destructor
     */
    ~libNetworkCommunication() override = default;
    /*!
     * @brief Returns the plugins name
     * @return The name of the plugin (as a const char*)
     */
    virtual const char* getPluginName() override;
    /*!
     * @brief Returns the version of the plugin
     * @return The plugin version
     */
    virtual const char* getPluginVersion() override;
    /*!
     * @brief Returns the plugin _type_
     * @return The the plugin is (as an enum)
     */
    virtual PluginLoader::PLUGINTYPE_t getPluginType() override;
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
    void SetPortToSendTo(int port) override;
    /*!
     * @brief Set the destination's address
     * @param destinationAddress The address we wish to send to
     */
    void SetDestinationAddress(char* destinationAddress) override;
    /*!
     * @brief Set whether TCP or UDP
     * @param tcpOrUDP 1 for TCP, 0 for UDP
     */
    void SetTCPOrUDP(int tcpOrUDP) override;
    /*!
     * @brief Supply extra information for connecting to a server
     * @param _servinfo A pointer to the address info we wish to use
     */
    void SetServInfo(addrinfo* _servinfo) override;
    /*!
     * @brief The Interface we want to connect over
     * @param iOInterface A shared_ptr containing the concrete implementation we wish to use
     */
    void SetInterface(std::shared_ptr<cFunctions::I_cNetComm> iOInterface) override;

    static bool _alreadyConnected;
private:
    /*! @brief The port we're conducting business on */
    int _portToSendTo;
    /*! @brief The Address we're sending to */
    std::string _destinationAddress;
    /*! @brief The socket used to bind and send on */
    int _outSocket;
    /*! @brief Do we want to connect on TCP, UDP, or both? */
    int _tcpOrUDP;
    /*! @brief The info of the server we're connecting  to */
    addrinfo* _servInfo;
    /*! @brief Wrapper class for using C socket functions */
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

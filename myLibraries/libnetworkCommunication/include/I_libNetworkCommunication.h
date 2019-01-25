/*!
 * @brief NetworkCommunication Interface Class
 *
 * @addtogroup NetworkCommunication Library
 *
 * @author hmarcks
 *
 * @date 24/12/2018
 */

#ifndef PROTOCOLDEVELOPER_I_NETWORKCOMMUNICATION_H
#define PROTOCOLDEVELOPER_I_NETWORKCOMMUNICATION_H

#include <I_communication.h>

namespace libNetworkCommunication
{
/*!
 * @brief The NetworkCommunication class
 */
class I_libNetworkCommunication
    : public Communication::I_communication
{
public:
    /*!
     * @brief Default destructor
     * N.B. auto-formatter puts '= 0' on next line
     */
    virtual ~I_libNetworkCommunication() = 0;
    /*!
     * @brief Sends data
     * @param payLoad_p The data we wish to send
     * @param size The size of the data
     * @return The size of the data sent
     */
    virtual ssize_t SendData(void* payLoad_p
                     , size_t size) = 0;
    /*!
     * @brief Recevies Data
     * @param payLoad_p Where to store the data we've recevied
     * @param size The size of the payload buffer
     * @return The size of the data received
     */
    virtual ssize_t ReceiveData(void* payLoad_p
                        , size_t size) = 0;
    /*!
     * @brief Establishes a connection with the remote
     * @return true for success, otherwise false
     */
    virtual bool EstablishConnection() = 0;
    /*!
     * @brief Disconnects from the target
     */
    virtual void Disconnect() = 0;
    /*!
     * @brief Sets the port we wish to send on
     * @param port The port we wish to send on
     */
    virtual void SetPortToSendTo(int port) = 0;
    /*!
     * @brief Set the destination's address
     * @param destinationAddress The address we wish to send to
     */
    virtual void SetDestinationAddress(char* destinationAddress) = 0;
    /*!
     * @brief Set whether TCP or UDP
     * @param tcpOrUDP 1 for TCP, 0 for UDP
     */
    virtual void SetTCPOrUDP(int tcpOrUDP) = 0;
    /*!
     * @brief Supply extra information for connecting to a server
     * @param _servinfo A pointer to the address info we wish to use
     */
    virtual void SetServInfo(addrinfo* _servinfo) = 0;
    /*!
     * @brief The Interface we want to connect over
     * @param iOInterface A shared_ptr containing the concrete implementation we wish to use
     */
    virtual void SetInterface(std::shared_ptr<cFunctions::I_cNetComm> iOInterface) = 0;
};
} /* namespace libNetworkCommunication */

#endif //PROTOCOLDEVELOPER_I_NETWORKCOMMUNICATION_H

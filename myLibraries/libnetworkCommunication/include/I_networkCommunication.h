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

namespace libNetworkCommunication
{
/*!
 * @brief The NetworkCommunication class
 */
class I_networkCommunication
{
public:
    //! Virtual Destuctor
    virtual ~I_networkCommunication();
    //! Sends Data
    virtual ssize_t SendData(void *payLoad_p, size_t size) = 0;
    //! Receives Data
    virtual ssize_t ReceiveData(void *payLoad_p, size_t size) = 0;
    //! Establishes a connection with the remote
    virtual bool EstablishConnection() = 0;
    //! Disconnects from the Remote
    virtual void Disconnect() = 0;
};

}

#endif //PROTOCOLDEVELOPER_I_NETWORKCOMMUNICATION_H

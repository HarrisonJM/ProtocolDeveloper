/*!
 * @brief Communication Interface
 *
 * Interface for providing Communication between different targets
 *
 * Payload will contain all required information.
 *
 * @addtogroup CommunicationHandler
 *
 * @date March 2018
 */

#ifndef PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H
#define PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H

#include <unistd.h>
#include <memory>

#include "I_cNetComm.h"
#include "I_plugin.h"

namespace Communication
{
/*!
 * @brief Defines the interface for listening
 */
class I_communication
{
public:
    /*! Default Destructor */
    ~I_communication() = default;
    /*!
     * @brief Sends Data to the remote
     * @param payLoad_p The payload we're sending
     * @param size The size of the payload
     * @return The number of bytes sent
     */
    virtual ssize_t SendData(void* payLoad_p
                             , size_t size) = 0;
    /*!
     * @brief Recevies Data from the Remote
     * @param payLoad_p Where to store the payload we're receiving
     * @param size The size of the buffer
     * @return The number of bytes sent written
     */
    virtual ssize_t ReceiveData(void* payLoad_p
                                , size_t size) = 0;
    /*!
     * @brief Establishes a Connection with the remote
     * @return True on success
     */
    virtual bool EstablishConnection() = 0;
    /*!
     * @brief Disconnects from the target
     */
    virtual void Disconnect() = 0;
};
}

#endif /* PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H */

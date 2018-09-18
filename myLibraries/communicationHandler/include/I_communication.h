/*!
 * @brief Communication Interface
 *
 * Interface for providing Communication over different interfaces
 *
 * Options will be defined by the user as some sort struct that can be easily cast
 * to and from the required data form. Payload will contain all required information.
 *
 * @addtogroup CommunicationHandler
 *
 * @date March 2018
 */

#ifndef PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H
#define PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H

#include <unistd.h>
#include "I_cNetComm.h"
#include <memory>

namespace Communication
{
    /*!
     * @brief Defines the interface for listening
     */
    class I_communication
    {
    public:
        //! Sends Data to the remote
        virtual ssize_t SendData(void *payLoad_p, size_t size) = 0;
        //! Recevies Data from the Remote
        virtual ssize_t ReceiveData(void *payLoad_p, size_t size) = 0;
        //! Establishes a Connection with the remote
        virtual bool EstablishConnection() = 0;
        //! Disconnects fromt the remote
        virtual void Disconnect() = 0;
        //! The Interface we want to connect over
        virtual void setInterface(cFunctions::I_cNetComm* iOInterface) = 0;
    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H

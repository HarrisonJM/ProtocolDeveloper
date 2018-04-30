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

namespace Communication
{
    /*!
     * @brief Defines the interface for listening
     */
    class CommunicationInterface
    {
    public:
        //! Sends Data to the remote
        virtual bool SendData(void *payLoad_p, int size) = 0;
        //! Recevies Data from the Remote
        virtual void ReceiveData(void *payLoad_p, int size) = 0;
        //! Establishes a Connection with the remote
        virtual bool EstablishConnection() = 0;
        //! Disconnects fromt the remote
        virtual void Disconnect() = 0;
    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H

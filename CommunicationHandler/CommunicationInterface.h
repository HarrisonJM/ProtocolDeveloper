//
// Created by hmarcks on 07/02/18.
//

#ifndef PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H
#define PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H

namespace CommunicationHandler
{
    class CommunicationInterface
    {
    public:
        // Options will be defined by the user as some sort struct that can be easily cast
        // to and from the required data form. Payload will contain all required information.
        virtual void SendData(void *payLoad_p) = 0;
        virtual void ReceiveData(void *payLoad_p) = 0;
    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONINTERFACE_H

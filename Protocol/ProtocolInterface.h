//
// Created by hmarcks on 10/02/18.
//

#ifndef PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H
#define PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

class ProtocolInterface
{
public:
    virtual void* resultReceived(void* payLoad) = 0;
    virtual void* dataToSend(void* payLoad) = 0;
};

#endif //PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

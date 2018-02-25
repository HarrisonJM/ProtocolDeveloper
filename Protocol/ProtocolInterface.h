#ifndef PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H
#define PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

template <class Result, class Send>
class ProtocolInterface
{
public:
    /* This function will RECEIVE from the server */
    virtual void *ResultReceived(void *payLoad) = 0;
    /* This function will send to the server */
    virtual bool DataToSend(void *payLoad) = 0;

    // This method will be used to decode any received results
    Result DecodeResult(void *payLoad);
    // This method will be used to encode any data that needs to be sent out
    Send EncodeData(void *payLoad);
    // Will return a pointer to the raw stored data
    void* getResult();
};

#endif //PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

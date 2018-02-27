#ifndef PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H
#define PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

/*
 * THE WAY IT WORKS IS:
 *
 * Test handler will request data generation from protocol
 * Testcase will request data
 * Testcase will pass data to comms ahndler to be sent
 * Comms handler will pass information back to the test
 * the test will pass it to the protocol to be decode (And it be returned)
 * Finally the test will log what the result was
 *
 */

typedef struct dataToSend
{
    void* data_p;
    int size;
} dataToSend;

class ProtocolInterface
{
public:
    virtual ~ProtocolInterface();

    // This method will be used to decode any received results
    virtual void DecodeResult(void *payLoad) = 0;
    // This method will be used to encode any data that needs to be sent out
    virtual dataToSend* GetDataToSend(void *payLoad, int size) = 0;
    // Will return a pointer to the raw stored data
    virtual void* getResult() = 0;
    // Returns any error code
    virtual int getResultCode() = 0;
};

#endif //PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

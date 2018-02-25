#include <string>
#include <ProtocolInterface.h>

#ifndef PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
#define PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H

namespace hwProt
{
    class HelloWorldProtocol : public ProtocolInterface<std::string, std::string>
    {
    public:
        HelloWorldProtocol();
        virtual ~HelloWorldProtocol();

        void *ResultReceived(void *payLoad) override;
        bool DataToSend(void *payLoad) override;

        // This method will be used to decode any received results
        std::string DecodeResult(void *payLoad);
        // This method will be used to encode any data that needs to be sent out
        std::string EncodeData(void *payLoad);
        // Will return a pointer to the raw stored data
        void* getResult();

    private:
        //! Will store the received result as "raw"
        void* result;
    };
}

#endif //PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
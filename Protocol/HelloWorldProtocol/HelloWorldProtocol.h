#include <string>
#include <ProtocolInterface.h>
#include <vector>

#ifndef PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
#define PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H

namespace hwProt
{
    class HelloWorldProtocol : public ProtocolInterface
    {
    public:
        HelloWorldProtocol();
        virtual ~HelloWorldProtocol();

        // This method will be used to decode any received results
        void DecodeResult(void *payLoad) override;
        // This method will return a pointer to data we want to send
        dataToSend* GetDataToSend(void *payLoad, int size) override;
        // Will return a pointer to the raw stored data
        void* getResult() override;
        // Will Return the last error code received
        int getResultCode() override;

    private:
        const char* returnHelloOrGoodbye();
        //! Will store the received result as "raw"
        void* result;
        //! Stores the error code
        int resultCode;
        //! vector that stores all our information
        std::vector<const char*> things;
        //! Bool that we can toggle to give us different things
        bool helloOrGoodbye;

    };
}

#endif //PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
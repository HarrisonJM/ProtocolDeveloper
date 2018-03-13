/*!
 * @brief HelloWorldProtocol
 *
 * The HelloWorldProtocol data generation and decoder, decalration
 *
 * @ingroup Protocol
 *
 * @date March 2018
 */
#include <string>
#include <ProtocolInterface.h>
#include <vector>

#ifndef PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
#define PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H

namespace hwProt
{
    /*!
     * @brief HelloWorldProtocol
     *
     * declares the header that will be used to help generate and decode
     * the helloworldprotocol information
     */
    class HelloWorldProtocol : public ProtocolInterface
    {
    public:
        HelloWorldProtocol();
        virtual ~HelloWorldProtocol();
        //! This method will be used to decode any received results
        void DecodeResult(void *payLoad) override;
        //! This method will return a pointer to data we want to send
        dataToSend *GetDataToSend() override;
        //! Will return a pointer to the raw stored data
        void* getResult() override;
        //! Will Return the last error code received
        int getResultCode() override;

    private:
        //! Decides what to return from the server
        const char* returnHelloOrGoodbye();
        //! Will store the received result as "raw"
        void* result;
        //! Stores the error code
        int resultCode;
        //! vector that stores all our information
        std::vector<const char*> possibleResults;
        //! Bool that we can toggle to give us different things
        bool helloOrGoodbye;

    };
}

#endif //PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
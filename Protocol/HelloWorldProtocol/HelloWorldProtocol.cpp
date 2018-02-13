#include <string>

#include "ProtocolInterface.h"
/*
 * This group of files will serve to act as a simple hello/goodby world protocol
 * The protocl willbe used as a test bed for various functions of the protdev program
 * It's first function will be simple to receive and send traffic
 * After that it will be extended to have and process error codes
 * It can then be extended to function with/as a sister protocol
 *
 */

class HelloWorldProtocol : public ProtocolInterface
{
public:
    HelloWorldProtocol();
    ~HelloWorldProtocol();


    void* resultReceived(void* payLoad) override;
    void* dataToSend(void* payLoad) override;

    // This method will be used to decode any received results
    std::string decodeResult(void* payLoad);
    // This method will be used to encode any data that needs to eb sent out
    std::string encodeData(void* payLoad);
};
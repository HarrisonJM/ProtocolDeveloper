#include <string>

#include "HelloWorldProtocol.h"
/* This group of files will serve to act as a simple hello/goodby world protocol
 * The protocl willbe used as a test bed for various functions of the protdev program
 * It's first function will be simple to receive and send traffic
 * After that it will be extended to have and process error codes
 * It can then be extended to function with/as a sister protocol
 */
namespace hwProt
{
    HelloWorldProtocol::HelloWorldProtocol()
    {

    }
    HelloWorldProtocol::~HelloWorldProtocol()
    {

    }
    // Stores the result within itself
    void* HelloWorldProtocol::ResultReceived(void *payLoad)
    {

    }
    bool HelloWorldProtocol::DataToSend(void *payLoad)
    {
        return false;
    }
    std::string HelloWorldProtocol::DecodeResult(void *payLoad)
    {
        return "";
    }
    std::string HelloWorldProtocol::EncodeData(void *payLoad)
    {
        return"";
    }
}

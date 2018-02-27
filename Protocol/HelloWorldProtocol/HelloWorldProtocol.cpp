#include <string>

#include "HelloWorldProtocol.h"
/*
 * This group of files will serve to act as a simple hello/goodby world protocol
 * The protocl willbe used as a test bed for various functions of the protdev program
 * It's first function will be simple to receive and send traffic
 * After that it will be extended to have and process error codes
 * It can then be extended to function with/as a sister protocol
 */
namespace hwProt
{
    HelloWorldProtocol::HelloWorldProtocol()
    : result(NULL),
      resultCode(0),
      helloOrGoodbye(0)
    {
        things.emplace_back("hello");
        things.emplace_back("goodbye");
        things.emplace_back("AAAAAAAAAAAAA");

    }
    //-----------------------------------------------------------------------------
    HelloWorldProtocol::~HelloWorldProtocol()
    {

    }
    //-----------------------------------------------------------------------------
    void HelloWorldProtocol::DecodeResult(void *payLoad)
    {
        auto* decodedData = static_cast<const char*>(payLoad);

        for (auto& thing : things)
        {
            if(std::string(thing) == std::string(decodedData))
                if (std::string(thing) != "ERROR\r\n")
                {
                    // Success
                    resultCode = 0;
                    break;
                }
            resultCode = 1;
            break;
        }
    }
    //-----------------------------------------------------------------------------
    dataToSend* HelloWorldProtocol::GetDataToSend(void *payLoad, int size)
    {
        dataToSend *D2s;
        D2s = static_cast<dataToSend*>(malloc(sizeof(dataToSend)));

        const char* hOG = returnHelloOrGoodbye();
        D2s->data_p = (void*)hOG;
        D2s->size = sizeof(hOG)-1;

        return D2s;
    }
    //-----------------------------------------------------------------------------
    void *HelloWorldProtocol::getResult()
    {
        return result;
    }
    //-----------------------------------------------------------------------------
    int HelloWorldProtocol::getResultCode()
    {
        return resultCode;
    }
    //-----------------------------------------------------------------------------
    const char *HelloWorldProtocol::returnHelloOrGoodbye()
    {
        helloOrGoodbye = helloOrGoodbye ^ true;
        return things[helloOrGoodbye];
    }
}

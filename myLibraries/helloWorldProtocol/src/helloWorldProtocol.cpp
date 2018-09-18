/*!
 * @brief HelloWorldProtocol
 *
 * The HelloWorldProtocol data generation and decoder, defintion
 *
 * @ingroup Protocol
 *
 * @date March 2018
 */
#include <string>

#include "HelloWorldProtocol.h"
/*
 * This group of files will serve to act as a simple hello/goodby world protocolHandler
 * The protocl willbe used as a test bed for various functions of the protdev program
 * It's first function will be simple to receive and send traffic
 * After that it will be extended to have and process error codes
 * It can then be extended to function with/as a sister protocolHandler
 */
namespace hwProt
{
    /*!
     * @brief default_constructor
     *
     * Emplaces possible results into a vector
     */
    HelloWorldProtocol::HelloWorldProtocol()
    : result(NULL),
      resultCode(0),
      helloOrGoodbye(0)
    {
        possibleResults.emplace_back("hello\r\n");
        possibleResults.emplace_back("goodbye\r\n");
        possibleResults.emplace_back("AAAAAAAAAAAAA");
    }

    /*!
     * @brief destructor
     */
    HelloWorldProtocol::~HelloWorldProtocol()
    {

    }

    /*!
     * @brief DecodeResult
     *
     * Decodes a payload and sets the return code accordingly
     *
     * @param payLoad The received Payload
     */
    void HelloWorldProtocol::DecodeResult(void *payLoad)
    {
        auto* decodedData = static_cast<const char*>(payLoad);

        for (auto& storedResults : possibleResults)
        {
            if(std::string(storedResults) == std::string(decodedData))
                if (std::string(storedResults) != "ERROR\r\n")
                {
                    // Success
                    resultCode = 0;
                    break;
                }
            resultCode = 1;
            break;
        }
    }

    /*!
     * @brief GetDataToSend
     *
     * Fetches the message and sets up the
     * struct we're going to send
     *
     * @todo needs work
     *
     * @return A pointer to the struct containg our information
     */
    dataToSend * HelloWorldProtocol::GetDataToSend()
    {
        dataToSend *D2s;
        D2s = static_cast<dataToSend*>(malloc(sizeof(dataToSend)));

        const char* hOG = returnHelloOrGoodbye();
        D2s->data_p = (void*)hOG;
        D2s->size = sizeof(hOG)-1;

        return D2s;
    }

    /*!
     * @brief getResult
     *
     * @return The last raw result data
     */
    void *HelloWorldProtocol::getResult()
    {
        return result;
    }

    /*!
     * @brief getResultCode
     *
     * @return The Last Result Code
     */
    int HelloWorldProtocol::getResultCode()
    {
        return resultCode;
    }

    /*!
     * @brief returnHelloOrGoodbye
     *
     * Toggles between sending hello or goodbye
     *
     * @return A string containing our message
     */
    const char *HelloWorldProtocol::returnHelloOrGoodbye()
    {
        helloOrGoodbye = helloOrGoodbye ^ true;
        return possibleResults[helloOrGoodbye];
    }
}

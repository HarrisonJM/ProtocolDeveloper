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
#include <HelloWorldProtocol.h>
#include <cstring>

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

int HelloWorldProtocol::_numberOfInstances = 0;

/*!
 * @brief Constructor, builds internal possible results vector
 */
HelloWorldProtocol::HelloWorldProtocol()
    : _result()
      , _resultCode(0)
      , helloOrGoodbye(false)
      , _curInstance(_numberOfInstances)
{
    _possibleResults.emplace_back("Hello, World!\r\n\0\0");
    _possibleResults.emplace_back("Goodbye, World!\r\n");
    _possibleResults.emplace_back("AAAAAAAAAAAAA");
}
/*!
 * @brief Decodes a payload and sets the return code accordingly
 * @param payLoad The received Payload
 */
void HelloWorldProtocol::DecodeResult(Protocol::DataStruct& payLoad)
{
    auto* decodedData = static_cast<const char*>(payLoad._data_p);

    for (auto& storedResults : _possibleResults)
    {
        if (std::string(storedResults) == std::string(decodedData))
        {
            if (std::string(storedResults) != "ERROR\r\n")
            {
                // Success
                _resultCode = 0;
                break;
            }
        }

        _resultCode = 1;
        break;
    }
}
/*!
 * @brief Fetches the message and sets up the struct we're going to send
 * @todo needs work
 * @return A pointer to the struct containg our information
 */
std::shared_ptr<Protocol::DataStruct> HelloWorldProtocol::GetDataToSend()
{
    Protocol::DataStruct ds;
    static short switcher = 0;

    auto packet = new char[20];
    std::memcpy(packet, _possibleResults[switcher].c_str(), 17);

    packet[17] = 0;
    packet[18] = 0;
    packet[19] = 0;
}
/*!
 * @brief getResult
 * @return The last raw result data
 */
std::shared_ptr<Protocol::DataStruct> HelloWorldProtocol::GetResult()
{
    return std::make_shared<Protocol::DataStruct>(_result);
}
/*!
 * @brief Returns the latest result code returned from the remote (if applicable)
 * @return The Last Result Code
 */
int HelloWorldProtocol::GetResultCode()
{
    return _resultCode;
}
/*!
 * @brief Sets the protocols datapoints
 * @param testDP The datapoints we're using
 */
void HelloWorldProtocol::SetDataPoints(testAnalyser2::dataPoint testDP)
{
    _testDP = testDP;
}

} /* namespace hwProt */

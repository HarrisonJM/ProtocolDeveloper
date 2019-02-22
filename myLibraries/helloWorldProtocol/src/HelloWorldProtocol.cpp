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
#include <iostream>

#include "HelloWorldProtocol.h"
/*
 * This group of files will serve to act as a simple hello/goodby world protocolHandler
 * The protocol will be used as a test bed for various functions of the protdev program
 * It's first function will be simple to receive and send traffic
 * After that it will be extended to have and process error codes
 * It can then be extended to function with/as a sister protocolHandler
 */
namespace hwProt
{

u_int8_t HelloWorldProtocol::_numberOfInstances = 0;

/*!
 * @brief Constructor, builds internal possible results vector
 */
HelloWorldProtocol::HelloWorldProtocol()
    : _result()
      , _resultCode(0)
      , helloOrGoodbye(false)
      , _curInstance(_numberOfInstances++)
{
    _possibleResults.emplace_back("Hello, World!\r\n\0\0\0");
    _possibleResults.emplace_back("Goodbye, World!\r\n\0\0\0");
    _possibleResults.emplace_back("ERROR\r\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
}
/*!
 * @brief Destructor, make threadsafe
 */
HelloWorldProtocol::~HelloWorldProtocol()
{
    _numberOfInstances--;
}
/*!
 * @brief Decodes a payload and sets the return code accordingly
 * @param payLoad The received Payload
 */
void HelloWorldProtocol::DecodeResult(std::shared_ptr<Protocol::DataStruct> payLoad)
{
    auto* decodedData = static_cast<const char*>(payLoad->_data_p);
    _result = *payLoad;

    for (auto& storedResult : _possibleResults)
    {
        if (storedResult == std::string(decodedData))
        {
            if (std::string(storedResult) != "ERROR\r\n")
            {
                // Success
                _resultCode = 0;
                break;
            }
        }
        // Error
        _resultCode = 1;
    }
}
/*!
 * @brief Fetches the message and sets up the struct we're going to send
 * @todo Needs work
 * @return A pointer to the struct containg our information
 */
std::shared_ptr<Protocol::DataStruct> HelloWorldProtocol::GetDataToSend()
{
    auto packet = new char[20];
    short selector = 0;

    if (_result._data_p == nullptr)
        selector = 2;
    else if (_possibleResults[1] == (char*) _result._data_p)
        selector = 0;
    else if (_possibleResults[0] == (char*) _result._data_p)
        selector = 1;
    else
        selector = 2;

    std::memcpy(packet
                , _possibleResults[selector].c_str()
                , 17);

    packet[17] = 0;
    packet[18] = 0;
    packet[19] = _curInstance;

    Protocol::DataStruct ds = {0};
    ds._data_p = packet;
    ds._size = 20;

    return std::make_shared<Protocol::DataStruct>(ds);
}
/*!
 * @brief Returns the last given result
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

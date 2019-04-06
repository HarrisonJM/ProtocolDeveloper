/*!
 * @brief BasicHelloConfiguration definition
 *
 * defines the basic hello configuration for simple back and forthing between
 * the ProtDev and the server. Sends Hello if it receives good bye, and vice versa
 *
 * @addtogroup HelloGoodByeServer
 *
 * @date March 2018
 *
 */
#include <string>
#include <iostream>
#include "BasicHello.h"

#define HELLO   "HELLO, WORLD!\n\r\0\0\0'\0'1"
#define GOODBYE "GOODBYE, WORLD!\n\r\0'\0'1"
#define ERROR "ERROR\r\n\0\0\0\0\0\0\0\0\0\0\0'\0'1"

namespace BasicHelloServer
{
//-----------------------------------------------------------------------------

/*!
 * @brief Sets the response
 *
 * @param[in] data A pointer to the data
 *
 * @return None
 */
void BasicHello::setResponse(const char* data)
{
    std::string properData(data);
    /*
    G  O  O  D  B  Y  E  ,     W  O  R  L  D  !  \n \r 00 00 XX|
    H  E  L  L  O  ,     W  O  R  L  D  !  \n \r \0 \0 00 00 XX|
    E  R  R  O  R  \r \n \0 \0 \0 \0 \0 \0 \0 \0 \0 \0 \0 \0 XX|
     */
    if (properData == HELLO)
        response = GOODBYE;
    else if (properData == GOODBYE)
        response = HELLO;
    else
        response = ERROR;
}

//-----------------------------------------------------------------------------

/*!
 * @brief decodes the data and passes it to setResponse
 *
 * @param dataIn Recieves and decodes the data
 *
 * @return None
 */
void BasicHello::receiveData(void* dataIn)
{
    setResponse(static_cast<char*>(dataIn));
}

//-----------------------------------------------------------------------------

/*!
 * @brief Returns the response
 *
 * @return Void pointer to the response
 */
void* BasicHello::sendData()
{
    return (void*) response.c_str();
}

//-----------------------------------------------------------------------------

/*!
 * @brief Constructor
 */
BasicHello::BasicHello()
    : response("")
{
}

//-----------------------------------------------------------------------------

/*!
 * @brief Destructor
 */
BasicHello::~BasicHello() = default;
}
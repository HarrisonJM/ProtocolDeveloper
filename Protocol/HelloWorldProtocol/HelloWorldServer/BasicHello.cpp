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
    void BasicHello::setResponse(const char *data)
    {
        std::string properData(data);

        if (properData == "hello")
            response = "Goodbye\r\n";
        else if (properData == "goodbye")
            response = "Hello\r\n";
        else
            response = "ERROR\r\n";
    }

//-----------------------------------------------------------------------------

/*  */
    /*!
     * @brief decodes the data and passes it to setResponse
     *
     * @param dataIn Recieves and decodes the data
     *
     * @return None
     */
    void BasicHello::receiveData(void *dataIn)
    {
        setResponse(static_cast<char *>(dataIn));
    }

//-----------------------------------------------------------------------------

    /*!
     * @brief Returns the response
     *
     * @return Void pointer to the response
     */
    void *BasicHello::sendData()
    {
        return (void *) response.c_str();
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
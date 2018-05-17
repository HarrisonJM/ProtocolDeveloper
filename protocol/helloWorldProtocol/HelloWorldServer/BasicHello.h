/*!
 * @brief BasicHelloConfiguration declaration
 *
 * @addtogroup HelloGoodByeServer
 *
 * @date March 2018
 */
#ifndef PROTOCOLDEVELOPER_BASICHELLO_H
#define PROTOCOLDEVELOPER_BASICHELLO_H

#include <string>

#include "ConfigurationInterface.h"

// BASIC CONFIGURATION
// This class will perform a basic i/o for testing
// When it is given a "hello" it sends back a "goodbye"
namespace BasicHelloServer
{
    /*!
     * @brief A basic hello class
     *
     * Receives and sends hello or goodbye
     */
    class BasicHello: public ConfigurationInterface
    {
    public:
        //! Constructor
        BasicHello();
        //! Destructor
        ~BasicHello() override;

        //! receives data
        void receiveData(void *dataIn) override;
        //! sends the desired response
        void* sendData() override;
        //! Sets the internal response string
        void setResponse(const char *data);

    private:
        //! The response we want to send out
        std::string response;
    };
}
#endif //PROTOCOLDEVELOPER_BASICHELLO_H
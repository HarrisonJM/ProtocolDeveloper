/*!
 * @brief ConfigurationInterface
 *
 * @addtogroup helloWorldServer
 *
 * @date March 2018
 */
#ifndef PROTOCOLDEVELOPER_CONFIGURATIONINTERFACE_H
#define PROTOCOLDEVELOPER_CONFIGURATIONINTERFACE_H

namespace BasicHelloServer
{
    /*!
     * @brief ConfigurationInterface
     *
     * defines how the connection handler interfaces with a configuration
     * Will be used later as a part fo a factory so that we can decide which type
     * of testing we wish to accomplish using the helloWord server
     */
    class ConfigurationInterface
    {
        public:
        //! Receives data from the OUTSIDE
        virtual void receiveData(void *dataIn) = 0;
        //! Sends data to the client
        virtual void *sendData() = 0;
        //! Destructor
        virtual ~ConfigurationInterface() = 0;
    };
}

#endif //PROTOCOLDEVELOPER_CONFIGURATIONINTERFACE_H

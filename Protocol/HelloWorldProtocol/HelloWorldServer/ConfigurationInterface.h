#ifndef PROTOCOLDEVELOPER_CONFIGURATIONINTERFACE_H
#define PROTOCOLDEVELOPER_CONFIGURATIONINTERFACE_H

// defines how the connection handler interfaces with a configuration
class ConfigurationInterface
{
public:
    // Receives data from the OUTSIDE
    virtual void receiveData(void* dataIn) = 0;
    // Sends data to the client
    virtual void* sendData() = 0;
};

#endif //PROTOCOLDEVELOPER_CONFIGURATIONINTERFACE_H

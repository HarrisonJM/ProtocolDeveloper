#ifndef PROTOCOLDEVELOPER_BASICHELLO_H
#define PROTOCOLDEVELOPER_BASICHELLO_H

#include <string>

#include "ConfigurationInterface.h"

// BASIC CONFIGURATION
// This class will perform a basic i/o for testing
// When it is given a "hello" it sends back a "goodbye"

class BasicHello : public ConfigurationInterface
{
public:
    BasicHello();
    ~BasicHello();

    void receiveData(void* dataIn) override;
    void* sendData() override;

    void setResponse(const char *data);

private:
    std::string response;
};

#endif //PROTOCOLDEVELOPER_BASICHELLO_H
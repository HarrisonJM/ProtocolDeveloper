//
// Created by hmarcks on 15/02/18.
//
#include <string>
#include <iostream>
#include "BasicHello.h"

//-----------------------------------------------------------------------------

/* Sets the response */
void BasicHello::setResponse(const char *data)
{
    std::string properData(data);

    if (properData == "hello")
        response = "Goodbye";
    else if (properData == "goodbye")
        response = "Hello";
    else
        response = "ERROR";
}

//-----------------------------------------------------------------------------

/* decodes the data and passes it to setResponse */
void BasicHello::receiveData(void* dataIn)
{
    setResponse(static_cast<char*>(dataIn));
}

//-----------------------------------------------------------------------------

/* returns the response */
void *BasicHello::sendData()
{
    return (void*)response.c_str();
}

//-----------------------------------------------------------------------------

BasicHello::BasicHello()
: response("")
{
}

//-----------------------------------------------------------------------------

BasicHello::~BasicHello() { }



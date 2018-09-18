/*!
 * @brief Is used to build netcommmanualtest
 *
 * Sends "hello" to the networkcommunicatiosn default port & address
 *
 */

#include "NetworkCommunication.h"

#include <iostream>
#include <cstring>

int main(void)
{
    Communication::NetworkCommunication nc;
    nc.EstablishConnection();

    void *payLoad = nullptr;
    payLoad = malloc(6);
    memcpy(payLoad, "hello", 6);
    nc.SendData(payLoad, 20);

    nc.ReceiveData(payLoad, 20);
    std::cout << "printing result: ";
    std::cout << static_cast<char*>(payLoad) << std::endl;

    return 0;
}
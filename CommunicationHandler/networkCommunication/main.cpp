//
// Created by hmarcks on 30/04/18.
//

#include "NetworkCommunication.h"

#include <iostream>

int main(void)
{
    Communication::NetworkCommunication nc;
    nc.EstablishConnection();

    void *payLoad = nullptr;
    payLoad = malloc(7);
    nc.SendData(payLoad, 20);
    nc.ReceiveData(payLoad, 20);
    std::cout << nc.getMsg() << std::endl;

    return 0;
}
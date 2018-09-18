
#include <stdio.h>
#include <iostream>
#include "helloWorld.h"

helloWorld::helloWorld()
{
    HelWor();
}

void helloWorld::HelWor()
{
    std::cout << "Hello, World!" << std::endl << std::flush;
}
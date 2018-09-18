#include <iostream>

#include "plug.h"

extern "C" plug* create_obj()
{
  return new plug;
};

extern "C" void destroy_obj(plug* pl_p)
{
  delete pl_p;
};

plug::plug()
{
  //I dunno lol
}

void plug::hello()
{
  std::cout << "Hello, World!" << std::endl;
}
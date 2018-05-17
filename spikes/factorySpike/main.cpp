#include "LoadDll.h"


int main(int argc, char** argv)
{
  LoadDLL *thing = new LoadDLL;

  interface *if_f = thing->getIF();

  if_f->hello();
}
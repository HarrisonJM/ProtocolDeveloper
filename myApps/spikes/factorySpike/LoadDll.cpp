
#include "LoadDll.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

LoadDLL::LoadDLL()
{ 
  lib_handle = dlopen("plugin/plug.so", RTLD_LAZY);
  if(!lib_handle)
  {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  create = (interface* (*)())dlsym(lib_handle, "create_obj");
  destroy = (void (*)(interface*))dlsym(lib_handle, "destroy_obj");

  if((error = dlerror()) != NULL)
  {
    fprintf(stderr, "%s\n", error);
    exit(1);
  }
}

LoadDLL::~LoadDLL()
{
  delete(if_f);
  dlclose(lib_handle);
}

interface* LoadDLL::getIF()
{
  this->if_f = (interface*)create();

  return if_f;
}

#include "interface.h"

//Loads our DLL
class LoadDLL
{
private:
  void *lib_handle;
  interface* (*create)();
  void (*destroy)(interface*);

  int x;
  char *error;

  interface *if_f;

public:
  LoadDLL();
  ~LoadDLL();

  interface* getIF();

private:
  //private methods

};
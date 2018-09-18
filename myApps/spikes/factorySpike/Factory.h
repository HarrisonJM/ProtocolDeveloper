#include <vector>
#include <string>
#include "interface.h"

/* 
 * Maybe should derive from some higher class that then decides if a protocolHandler,
 * JSON, commhandler plugin should be returned. Or we could just create three
 * instances that just hold a vector of different plugins.
 *  
 */
class Factory
{
public:
  Factory();
  Factory(std::string identifier);
  ~Factory();

private:
  std::string identifier;
  void *lib_handle;

};
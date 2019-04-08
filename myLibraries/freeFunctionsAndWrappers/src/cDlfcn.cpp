#include <dlfcn.h>

#include "freeFunctionsAndWrappers/cDlfcn.h"

namespace cFunctions
{

void *cDlfcn::dlopenHandle(const char *__file
                           , int __mode)
{
    return dlopen(__file
                        , __mode);
}
int cDlfcn::dlcloseHandle(void *__handle)
{
    return dlclose(__handle);
}
void *cDlfcn::dlsymbol(void *__handle
                       , const char *__name)
{
    return dlsym(__handle
                    , __name);
}
char *cDlfcn::dlerrorStr(void)
{
    return dlerror();
}
}
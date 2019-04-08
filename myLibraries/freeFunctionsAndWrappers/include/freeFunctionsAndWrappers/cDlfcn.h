/*!
 * @brief the dlfcn library in the form of a contained class for unit testing
 * @author hmarcks
 * @date 8/4/19
 */

#ifndef __PROTOCOLDEVELOPER_CDLFCN_H__
#define __PROTOCOLDEVELOPER_CDLFCN_H__

#include <I_cDlfcn.h>

namespace cFunctions
{
class cDlfcn
        : public I_cDlfcn
{
public:
    void *dlopenHandle(const char *__file
                       , int __mode) override;
    int dlcloseHandle(void *__handle) override;
    void *dlsymbol(void *__handle
                   , const char *__name) override;
    char *dlerrorStr(void) override;
};
}

#endif //__PROTOCOLDEVELOPER_CDLFCN_H__

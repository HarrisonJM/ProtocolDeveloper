/*!
 * @brief Interface for the dlfcn header for unit testing the plugin loader library
 * @author harrison marcks
 * @date 8/04/19
 */

#ifndef __PROTOCOLDEVELOPER_I_CDLFCN_H__
#define __PROTOCOLDEVELOPER_I_CDLFCN_H__

namespace cFunctions
{
class I_cDlfcn
{
public:
    virtual void *dlopenHandle(const char *__file
                               , int __mode) = 0;

    virtual int dlcloseHandle(void *__handle) = 0;

    virtual void *dlsymbol(void *__handle
                           , const char *__name) = 0;
    virtual char *dlerrorStr(void) = 0;
};
}

#endif //__PROTOCOLDEVELOPER_I_CDLFCN_H__

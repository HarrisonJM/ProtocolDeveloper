/*!
 * @brief gmock mocks for the cDflcn class
 * @author Harrison Marcks
 * @date 8/4/19
 * @addtogroup mockLibrary
 * @{
 */

#include "gmock/gmock.h"
#include "I_cDlfcn.h"

#ifndef __PROTOCOLDEVELOPER_CDLFCNMOCKS_H__
#define __PROTOCOLDEVELOPER_CDLFCNMOCKS_H__

namespace cFunctions
{
class dlfcnMocks : public I_cDlfcn
{
public:
    MOCK_METHOD2(dlopenHandle
                 , void*(
            const char*, int));
    MOCK_METHOD1(dlcloseHandle
                 , int(void * ));
    MOCK_METHOD2(dlsymbol
                 , void*(
            void*, const char*));
    MOCK_METHOD0(dlerrorStr
                 , char*(
            void));
};
}
/*! @} */
#endif //__PROTOCOLDEVELOPER_CDLFCNMOCKS_H__

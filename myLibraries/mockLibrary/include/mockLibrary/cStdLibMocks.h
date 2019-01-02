/*!
 * @brief defines all the mocks required to mock the C socket functions
 *
 * @addtogroup mocksLibrary
 *
 * @date May 2018
 *
 */

#ifndef PROTOCOLDEVELOPER_CSTDLIBMOCKS_H
#define PROTOCOLDEVELOPER_CSTDLIBMOCKS_H

#include "gmock/gmock.h"
#include "../../../../freeFunctionsAndWrappers/include/I_cStdLib.h"

namespace cFunctions
{

class cStdLibMocks: public I_cStdLib
{
public:
    MOCK_METHOD1(malloc
                 , void* (size_t
        __size));

};

} /* namespace cFunctions */

#endif /* PROTOCOLDEVELOPER_CSTDLIBMOCKS_H */
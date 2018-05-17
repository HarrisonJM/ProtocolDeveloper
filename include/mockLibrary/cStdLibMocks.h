/*!
 * @brief defines all the mocks required to mock the C socket functions
 *
 * @addtogroup mocksLibrary
 *
 * @date May 2018
 *
 */

#include "gmock/gmock.h"
#include "interfaces/I_cStdLib.h"

namespace cFunctions
{

class cStdLibMocks: public I_cStdLib
{
public:
    MOCK_METHOD1(cMalloc, void*(size_t __size));

};

} /* namespace cFunctions */
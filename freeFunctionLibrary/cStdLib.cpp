/*!
 * @brief Wrapper class to allow mocking the network communication libraries
 * provided from C
 *
 * @addtogroup cMocking
 *
 * @date 09/05/2018
 */
#include "cStdLib.h"


namespace cFunctions
{

void *cStdLib::cMalloc(size_t __size)
{
    return malloc(__size);
}

}
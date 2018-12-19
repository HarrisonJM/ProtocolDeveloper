/*!
 * @brief Wrapper class to allow mocking the network communication libraries
 * provided from C
 *
 * @addtogroup cMocking
 *
 * @date 09/05/2018
 */
#include "freeFunctionsAndWrappers/cStdLib.h"


namespace cFunctions
{

void *cStdLib::cMalloc(size_t __size)
{
    return malloc(__size);
}

int abs(int j)
{
    return std::abs(j);
}

ldiv_t ldiv(long numerator, long denominator)
{
    return std::ldiv(numerator, denominator);
}

}
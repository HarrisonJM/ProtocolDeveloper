/*!
 * @brief wrapper class for funtions in the stdlib C library
 *
 * @addtogroup cMocking
 *
 * @date May 2018
 */

#ifndef PROTOCOLDEVELOPER_I_CSTDLIB_H
#define PROTOCOLDEVELOPER_I_CSTDLIB_H

#include <stdlib.h>

namespace cFunctions
{

//! cstdlib interface for mocking
class I_cStdLib
{
public:
    //! man 3 malloc
    virtual void* cMalloc(size_t size) = 0;
    //! man 3 abs
    virtual int abs(int j) = 0;
    //! man 3 ldiv
    virtual ldiv_t ldiv(long numerator, long denominator) = 0;
};

} /* namespace cFunctions */


#endif //PROTOCOLDEVELOPER_I_CSTDLIB_H

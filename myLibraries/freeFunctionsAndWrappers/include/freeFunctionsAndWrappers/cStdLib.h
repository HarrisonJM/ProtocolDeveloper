/*!
 * @brief class wrapper for the C stdlib functions
 *
 * @addtogroup cMocking
 *
 * @date 17/05/2018
 */
#include "I_cStdLib.h"

#ifndef PROTOCOLDEVELOPER_CSTDLIB_H
#define PROTOCOLDEVELOPER_CSTDLIB_H


namespace cFunctions
{

//! Class header for stdlib wrapper
class cStdLib: public I_cStdLib
{
public:
    //! man 3 malloc
    void* malloc(size_t __size) override;
    //! man 3 abs
    int abs(int j) override;
    //! man 3 ldiv
    ldiv_t ldiv(long numerator, long denominator) override;
};

} /* namespace cFunctions */

#endif //PROTOCOLDEVELOPER_CSTDLIB_H

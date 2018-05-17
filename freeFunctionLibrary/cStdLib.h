/*!
 * @brief class wrapper for the C stdlib functions
 *
 * @addtogroup cMocking
 *
 * @date 17/05/2018
 */
#include "interfaces/I_cStdLib.h"

#ifndef PROTOCOLDEVELOPER_CSTDLIB_H
#define PROTOCOLDEVELOPER_CSTDLIB_H


namespace cFunctions
{

//! Class header for stdlib wrapper
class cStdLib: public I_cStdLib
{
public:
    //! man 3 malloc
    void *cMalloc(size_t __size) override;
};

} /* namespace cFunctions */

#endif //PROTOCOLDEVELOPER_CSTDLIB_H

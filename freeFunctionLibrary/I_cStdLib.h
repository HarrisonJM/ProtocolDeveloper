/*!
 * @brief wrapper class for funtions in the stdlib C library
 *
 * @addtgroup cMocking
 *
 * @date May 2018
 */

#include <stdlib.h>

#ifndef PROTOCOLDEVELOPER_I_CSTDLIB_H
#define PROTOCOLDEVELOPER_I_CSTDLIB_H

namespace cFunctions
{

class I_cStdLib
{
public:
    virtual void* cMalloc(size_t size) = 0;

};

} /* namespace cFunctions */


#endif //PROTOCOLDEVELOPER_I_CSTDLIB_H

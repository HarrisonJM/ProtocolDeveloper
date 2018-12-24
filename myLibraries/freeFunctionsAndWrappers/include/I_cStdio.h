/*!
 * @brief Interface for c stdio functions
 *
 * @author hmarcks
 *
 * @addtogroup cFunctions
 *
 * @date 18/12/18
 */

#ifndef PROTOCOLDEVELOPER_I_CSTDIO_H
#define PROTOCOLDEVELOPER_I_CSTDIO_H

#include <cstddef>
#include <cstdarg>

namespace cFunctions
{
class I_cStdio
{
public:
    ~I_cStdio() = default;
    /*! man 3 printf */
    virtual int snprintf(char* str
                         , size_t size
                         , const char* format
                         , ...) = 0;
};
} /* namespace cFunctions */

#endif /* PROTOCOLDEVELOPER_I_CSTDIO_H */

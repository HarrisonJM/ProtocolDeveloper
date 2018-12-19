/*!
 * @brief Header for normal C function wrapper
 *
 * @author hmarcks
 *
 * @addtogroup cFunctions
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_CSTDIO_H
#define PROTOCOLDEVELOPER_CSTDIO_H

#include <I_cStdio.h>

namespace cFunctions
{

class cStdio
    : public I_cStdio
{
public:
    cStdio() = default;
    ~cStdio() = default;
    /*! man 3 printf */
    int snprintf(char* str
                 , size_t size
                 , const char* format
                 , ...) override;
private:
};
} /* namespace cFunctions */

#endif /* PROTOCOLDEVELOPER_CSTDIO_H */

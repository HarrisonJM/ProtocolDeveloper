/*!
 * @brief
 *
 * @addtogroup
 *
 * @date
 */
#include "interfaces/I_cStdLib.h"

#ifndef PROTOCOLDEVELOPER_CSTDLIB_H
#define PROTOCOLDEVELOPER_CSTDLIB_H


namespace cFunctions
{

class cStdLib: public I_cStdLib
{
public:
    void *cMalloc(size_t __size) override;
};

} /* namespace cFunctions */

#endif //PROTOCOLDEVELOPER_CSTDLIB_H

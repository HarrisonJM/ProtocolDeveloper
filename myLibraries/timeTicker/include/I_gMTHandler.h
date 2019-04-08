/*!
 * @brief Interface for the gmt handler class
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */

#ifndef PROTOCOLDEVELOPER_I_GMTHANDLER_H
#define PROTOCOLDEVELOPER_I_GMTHANDLER_H

#include <timeTicker/timeTickerCommon.h>

namespace timeTicker
{
class I_gMTHandler
{
public:
    ~I_gMTHandler() = default;
    virtual int PrintGMTOffset(const struct tm* theTimeTM_p
                               , char* buffer_p
                               , size_t length) const = 0;
    virtual TTRetCode_E GetGMTOffset(const struct tm* tm_p
                                     , TTGMTOffset_t* offset_p) const = 0;
private:
};
} /* namespace timeTicker */
#endif /* PROTOCOLDEVELOPER_I_GMTHANDLER_H */

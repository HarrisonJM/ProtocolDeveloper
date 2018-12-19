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

namespace TimeTicker
{
class I_gMTHandler
{
public:
    ~I_gMTHandler() = default;
    virtual int PrintGMTOffset(const struct tm* theTimeTM_p
                               , char* buffer_p
                               , size_t length) = 0;
    virtual int GetGMTOffset(const struct tm* tm_p
                             , TTGMTOffset_t* offset_p) = 0;
private:
};
} /* namespace TimeTicker */
#endif /* PROTOCOLDEVELOPER_I_GMTHANDLER_H */

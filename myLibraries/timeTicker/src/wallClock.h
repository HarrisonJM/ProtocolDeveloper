/*!
 * @brief Declaration for the WallClock class, works exclusively in seconds
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_WALLCLOCK_H
#define PROTOCOLDEVELOPER_WALLCLOCK_H

#include <ctime>
#include <memory>

#include <I_gMTHandler.h>
#include "timeTickerDefinitions.h"
#include "timeTicker/timeTickerCommon.h"
#include "../../freeFunctionsAndWrappers/include/I_cStdio.h"
#include "../../freeFunctionsAndWrappers/include/I_cStdLib.h"

namespace TimeTicker
{

class WallClock
{
public:
    WallClock();
    WallClock(std::unique_ptr<I_gMTHandler> gmtHandler
              , std::unique_ptr<cFunctions::I_cStdio> cstdioFunctions
              , std::unique_ptr<cFunctions::I_cStdLib> cstdlibFunctions
    );
    ~WallClock() = default;
    const char* getTimeToString(time_t theTime);
private:
    /* Used for caching between uses */
    char _timeStampBuffer[TT_TIMEVAL_STR_SIZE];
    TT_timeval_t _lastTime;
    int _lastHour;

    std::unique_ptr<I_gMTHandler> _gmtModule;
    std::unique_ptr<cFunctions::I_cStdio> _cstdioModule;
    std::unique_ptr<cFunctions::I_cStdLib> _cstdlibModule;
};
} /* TimeTicker */

#endif /* PROTOCOLDEVELOPER_WALLCLOCK_H */

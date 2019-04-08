/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 18/12/18
 */

#include <freeFunctionsAndWrappers/cStdio.h>
#include <freeFunctionsAndWrappers/cStdLib.h>
#include <gMTHandler.h>

#include "timeTicker/wallClock.h"

namespace timeTicker
{
/*!
 * @brief Default constructor
 */
WallClock::WallClock()
    : _gmtModule(std::make_unique<GMTHandler>())
      , _cstdioModule(std::make_unique<cFunctions::cStdio>())
      , _cstdlibModule(std::make_unique<cFunctions::cStdLib>())
{
}
/*!
 * @brief Modular constructor, used to reaplce different std libraries
 * @param gmtHandler The gmtHandler
 * @param cstdioFunctions The stdio or equivalent functions
 * @param cstdlibFunctions The stdlib or equivalent functions
 */
WallClock::WallClock(std::unique_ptr<I_gMTHandler> gmtHandler
                     , std::unique_ptr<cFunctions::I_cStdio> cstdioFunctions
                     , std::unique_ptr<cFunctions::I_cStdLib> cstdlibFunctions)
    : _gmtModule(std::move(gmtHandler))
      , _cstdioModule(std::move(cstdioFunctions))
      , _cstdlibModule(std::move(cstdlibFunctions))
{
}
/*!
 * @brief Returns the time as a string (seconds precision)
 * @param theTime The time (in seconds) we wish to know
 * @return A Char* containing the timestamp
 */
const char* WallClock::getTimeToString(time_t theTime)
{
    TT_tm_t theTimeTM = {0};
    char* retStr_P = nullptr;

    tzset();
    (void) localtime_r(&theTime
                       , &theTimeTM);

    // Print the time fields into the buffer
    size_t result = std::strftime(_timeStampBuffer
                                  , sizeof(_timeStampBuffer)
                                  , "%Y-%m-%d %H:%M:%S"
                                  , &theTimeTM);
    if (result > 0)
    {
        retStr_P = _timeStampBuffer;
    }
    else
    {
        retStr_P = nullptr;
    }

    return retStr_P;
}
} /* timeTicker */
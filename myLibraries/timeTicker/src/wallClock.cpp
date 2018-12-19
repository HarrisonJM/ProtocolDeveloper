/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 18/12/18
 */

#include <timeTicker/timeTickerCommon.h>
#include "wallClock.h"

namespace TimeTicker
{

wallClock::WallClock()
{
}

const char* WallClock::getTimeToString(time_t theTime)
{
    timeM_t theTimeTM = {0};
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
/*!
 * @brief Prints the time given in tm_p according to RFC 4517 (YYYYMMDDHHMMSS[.fff][Z|[+-]hhmm])
 * @param tm_p
 * @param microsecs_p
 * @param fractionDigits
 * @param buf_p
 * @param bufSize
 * @return
 */
TTRetCode WallClock::PrintGeneralizedTime(const timeM_t* tm_p
                                           , unsigned int* microsecs_p
                                           , unsigned int fractionDigits
                                           , char* buf_p
                                           , size_t bufSize)
{
    TTRetCode_E retCode = TT_RC_FAILURE;

    if (!tm_p || !buf_p || (fractionDigits > 6))
    {
        return TT_RC_FAILURE;
    }

    // Get the GMT offset from the input time
    TTGMTOffset gmtOffset = {0};
    if (getGetGMTOffset(tm_p
                        , &gmtOffset))
    {
        return TT_RC_FAILURE;
    }

    // Print the struct tm into the buffer
    int numPrinted = static_cast<int>(std::strftime(buf_p
                                                    , bufSize
                                                    , "%Y%m%d%H%M%S"
                                                    , tm_p));
    if (numPrinted <= 0)
    {
        return TT_RC_FAILURE;
    }

    // Remaining buffer size is reduced
    bufSize -= numPrinted;
    buf_p += numPrinted;

    // Print the optional microseconds component
    if (microsecs_p && fractionDigits)
    {
        char microStr[10];
        std::snprintf(microStr
                      , sizeof(microStr)
                      , "%06d"
                      , *microsecs_p);
        numPrinted = std::snprintf(buf_p
                                   , bufSize
                                   , ".%.*s"
                                   , fractionDigits
                                   , microStr);

        // snprintf output was truncated, return error
        if (numPrinted >= (int) bufSize)
        {
            return TT_RC_FAILURE;
        }
            // snprintf output error, return error
        else if (numPrinted < 0)
        {
            return TT_RC_FAILURE;
        }

        // Remaining buffer size is reduced
        bufSize -= numPrinted;
        buf_p += numPrinted;
    }

    // Print the GMT offset
    if (gmtOffset.totalSeconds != 0)
    {
        char offsetSign;
        int gmtOffHour;
        int gmtOffMins;

        if (gmtOffset.totalSeconds > 0)
        {
            offsetSign = '+';
            gmtOffHour = gmtOffset.hours;
            gmtOffMins = gmtOffset.minutes;
        }
        else
        {
            offsetSign = '-';
            gmtOffHour = std::abs(gmtOffset.hours);
            gmtOffMins = std::abs(gmtOffset.minutes);
        }

        numPrinted = std::snprintf(buf_p
                                   , bufSize
                                   , "%c%02d%02d"
                                   , offsetSign
                                   , gmtOffHour
                                   , gmtOffMins);
    }
    else
    {
        numPrinted = std::snprintf(buf_p
                                   , bufSize
                                   , "%c"
                                   , 'Z');
    }

    // snprintf output was truncated, return error
    if (numPrinted >= (int) bufSize)
    {
        return TTRetCode::TT_RC_FAILURE;
    }
        // snprintf output error, return error
    else if (numPrinted < 0)
    {
        return TTRetCode::TT_RC_FAILURE;
    }
    else
    {
        return TTRetCode::TT_RC_SUCCESS;
    }
}

int WallClock::getClockGetTime(TTTimeClockId clockId
                                , timespec_t* time_p)
{
    return clock_gettime(clockId
                         , time_p);
}

} /* TimeTicker */
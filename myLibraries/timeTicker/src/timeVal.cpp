/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 18/12/18
 */

#include "timeTicker/wallClock.h"
#include <timeTicker/timeTickerCommon.h>
#include <sys/time.h>
#include <cstdio>
#include <cstring>
#include "timeTickerDefinitions.h"
#include "gMTHandler.h"
#include <freeFunctionsAndWrappers/cStdio.h>

#include "timeTicker/timeVal.h"

namespace timeTicker
{
/*!
 * @brief Default Constructor
 */
TimeVal::TimeVal()
    : _gmtHandler(std::make_unique<GMTHandler>())
      , _stdioModule(std::make_unique<cFunctions::cStdio>())
{}
/*!
 * @brief Allows the underlying modules to be swapped out with something more non-standard
 * @param gmtHandler The gmt Handler we wish to use
 * @param stdioModule The stdio module we wish to use
 */
TimeVal::TimeVal(std::unique_ptr<I_gMTHandler> gmtHandler
                 , std::unique_ptr<cFunctions::I_cStdio> stdioModule)
    : _gmtHandler(std::move(gmtHandler))
      , _stdioModule(std::move(stdioModule))
{
}
/*!
 * @brief Returns a char string containing a timestamp generated using struct timeval
 * (Microsecond Precision)
 * @return The timestamp in YYYY-MM-DD HH:MM:SS.FFF[(+|-HHMM)|Z]
 */
const char* TimeVal::getTimeStampMicro()
{
    // Get the current time (seconds, microseconds)
    TT_timeval_t theTimeTV = {0};
    (void) gettimeofday(&theTimeTV
                        , nullptr);

    return _genTimevalToString(&theTimeTV
                               , TT_NUM_MICROSECS_DIGITS);
}
/*!
 * @brief Returns a char string containing a timestamp generated using struct timeval
 * (Millisecond Precision)
 * @return The timestamp in YYYY-MM-DD HH:MM:SS.FFF[(+|-HHMM)|Z]
 */
const char* TimeVal::getTimestampMilli()
{
    // Get the current time (seconds, microseconds)
    TT_timeval_t theTimeTV = {0};
    (void) gettimeofday(&theTimeTV
                        , nullptr);

    return _genTimevalToString(&theTimeTV
                               , TT_NUM_MILISECS_DIGITS);
}
/*!
 * @brief Returns a char string containing a timestamp generated using struct timeval
 * @param tv The timeval struct we wish to get the time for
 * @return The timestamp in YYYY-MM-DD HH:MM:SS.FFF[(+|-HHMM)|Z]
 */
const char* TimeVal::getStringMicro(const TT_timeval_t* tv)
{
    return _genTimevalToString(tv
                               , TT_NUM_MICROSECS_DIGITS);
}
/*!
 * @brief Generic function specifically for generating the timeval timestamp
 * @param tv The timeval struct we want the timestamp for
 * @param numDecimalDigits The level of precision we want
 * @return The timeval in a string format
 */
const char* TimeVal::_genTimevalToString(const TT_timeval_t* tv
                                         , size_t numDecimalDigits)
{
    // Index of the GMT offset substring
    const size_t tzOffsetIndex = TT_FRACTION_OFFSET + numDecimalDigits;
    const char* retVal = nullptr;

    /*
     * localtime_v and strftime are time consuming. Only bother to do them if the
     * second is different to the last time we got called.
     * If the second is the same then we just need to print the milliseconds.
     */
    if (_lastTime.tv_sec != tv->tv_sec)
    {
        _lastTime.tv_sec = tv->tv_sec;

        // Convert UTC time to broken-time struct tm
        auto secs = static_cast<time_t>(tv->tv_sec);
        TT_tm_t theTimeTM = {0};
        tzset();
        TT_tm_t* theTimeTM_p = localtime_r(&secs
                                           , &theTimeTM);

        if (theTimeTM_p)
        {
            // Print the time fields into the buffer
            (void) std::strftime(_timeStampBuffer
                                 , TT_TIMEVAL_STR_SIZE
                                 , "%Y-%m-%d %H:%M:%S."
                                 , theTimeTM_p);

            // Re-generate the GMT offset every hour
            if (_lastHour != theTimeTM_p->tm_hour)
            {
                _lastHour = theTimeTM_p->tm_hour;
                _gmtHandler->PrintGMTOffset(theTimeTM_p
                                           , _timeStampBuffer + tzOffsetIndex
                                           , TT_TIMEVAL_STR_SIZE - tzOffsetIndex);
            }

            // Print the fractional component
            char fractionBuffer[TT_MAX_FRACTION_SIZE + 1];
            (void) std::snprintf(fractionBuffer
                                 , sizeof(fractionBuffer)
                                 , "%06u"
                                 , static_cast<unsigned int>((tv->tv_usec)));

            // Only copy the number of digits requested
            std::memcpy(_timeStampBuffer + TT_FRACTION_OFFSET
                        , fractionBuffer
                        , numDecimalDigits);
            retVal = _timeStampBuffer;
        }
    }

    return retVal;
}
/*!
 * @brief Prints the time given in tm_p according to RFC 4517 (YYYYMMDDHHMMSS[.fff][Z|[+-]hhmm])
 * @param tm_p The tm struct we wish to use (that contains the time)
 * @param microsecs_p Where the microseconds are located
 * @param fractionDigits How many places after the DP do we want
 * @param buf_p Where to store the time stamp
 * @param bufSize How large is the buffer
 * @return false for failure, true on success
 */
TTRetCode TimeVal::PrintGeneralizedTime(const TT_tm_t* tm_p
                                        , unsigned int* microsecs_p
                                        , unsigned int fractionDigits
                                        , char* buf_p
                                        , size_t bufSize)
{
    if (!tm_p || !buf_p || (fractionDigits > 6))
    {
        return TT_RC_FAILURE;
    }

    // Get the GMT offset from the input time
    TTGMTOffset gmtOffset = {0};
    if (_gmtHandler->GetGMTOffset(tm_p
                                  , &gmtOffset))
    {
        return TT_RC_FAILURE;
    }

    // Print the struct tm into the buffer
    auto numPrinted = static_cast<int>(strftime(buf_p
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
        _stdioModule->snprintf(microStr
                               , sizeof(microStr)
                               , "%06d"
                               , *microsecs_p);
        numPrinted = _stdioModule->snprintf(buf_p
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
            gmtOffHour = abs(gmtOffset.hours);
            gmtOffMins = abs(gmtOffset.minutes);
        }

        numPrinted = _stdioModule->snprintf(buf_p
                                            , bufSize
                                            , "%c%02d%02d"
                                            , offsetSign
                                            , gmtOffHour
                                            , gmtOffMins);
    }
    else
    {
        numPrinted = _stdioModule->snprintf(buf_p
                                            , bufSize
                                            , "%c"
                                            , 'Z');
    }

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
    else
    {
        return TT_RC_SUCCESS;
    }
}
} /* timeTicker */
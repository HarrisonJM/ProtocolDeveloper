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
#include <sys/time.h>
#include <cstdio>
#include <cstring>
#include "timeVal.h"
#include "timeTickerDefinitions.h"

namespace TimeTicker
{

TimeVal::TimeVal()
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
    timeval_t theTimeTV = {0};
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
    timeval_t theTimeTV = {0};
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
const char* TimeVal::getStringMicro(const timeval_t* tv)
{
    return _genTimevalToString(tv
                               , TT_NUM_MICROSECS_DIGITS);
}
/*!
 * @brief Generic function specifically for generating the timeval timestamp
 * @param tv The timeval struct we want the timestamp for
 * @param numDecimalDigits The level of precision we want
 * @return
 */
const char* TimeVal::_genTimevalToString(const timeval_t* tv
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
        timeM_t theTimeTM = {0};
        tzset();
        timeM_t* theTimeTM_p = localtime_r(&secs
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
                getPrintGMTOffset(theTimeTM_p
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
} /* TimeTicker */
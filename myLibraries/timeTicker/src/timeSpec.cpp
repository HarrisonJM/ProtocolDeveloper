/*!
 * @brief Implementation for all TimeSpec Related functions
 *
 * @author hmarcks
 *
 * @addtogroup timeSpec
 *
 * @date 18/12/18
 */

#include <timeTicker/timeTickerCommon.h>
#include <cstdint>
#include "timeSpec.h"
#include "timeTickerDefinitions.h"

namespace TimeTicker
{

TimeSpec::TimeSpec()
{
}

int TimeSpec::getTimeSpecSubtract(const timespec_t* first_p
                                   , const timespec_t* second_p
                                   , timespec_t* result_p)
{
    timespec_t localFirst = {0};
    timespec_t localSecond = {0};
    const long int NUM_NANO_SECS = 1000000000;

    // Copy first_p and second_p
    localFirst = *first_p;
    localSecond = *second_p;

    // Perform the carry for the later subtraction by updating y.
    if (localFirst.tv_nsec < localSecond.tv_nsec)
    {
        uint64_t nsec = (localSecond.tv_nsec - localFirst.tv_nsec)/NUM_NANO_SECS + 1;
        localSecond.tv_nsec -= NUM_NANO_SECS*nsec;
        localSecond.tv_sec += nsec;
    }

    if (localFirst.tv_nsec - localSecond.tv_nsec > NUM_NANO_SECS)
    {
        uint64_t nsec = (localFirst.tv_nsec - localSecond.tv_nsec)/NUM_NANO_SECS;
        localSecond.tv_nsec += 1000000*nsec;
        localSecond.tv_sec -= nsec;
    }

    /* Compute the time remaining to wait. tv_usec  is certainly positive. */
    result_p->tv_sec = localFirst.tv_sec - localSecond.tv_sec;
    result_p->tv_nsec = localFirst.tv_nsec - localSecond.tv_nsec;

    /* Return 1 if result is negative. */
    return localFirst.tv_sec < localSecond.tv_sec;
}
void TimeSpec::getTimeSpecAdd(const timespec_t* first_p
                              , const timespec_t* second_p
                              , timespec_t* result_p)
{
    result_p->tv_sec = first_p->tv_sec + second_p->tv_sec;

    int64_t nanos = first_p->tv_nsec + second_p->tv_nsec;

    if (nanos > TT_NANOS_PER_SEC)
    {
        result_p->tv_nsec = nanos - TT_NANOS_PER_SEC;
        result_p->tv_sec += 1;
    }
    else
    {
        result_p->tv_nsec = nanos;
    }
}
int64_t TimeSpec::getTimeSpecDiff(const timespec_t* timeA_p
                                  , const timespec_t* timeB_p)
{
    return ((timeA_p->tv_sec*1000000000) + timeA_p->tv_nsec) -
        ((timeB_p->tv_sec*1000000000) + timeB_p->tv_nsec);
}
int64_t TimeSpec::getTimeSpecDiffNS(const timespec_t* timeA_p
                                    , const timespec_t* timeB_p)
{
    return  (TT_SECS_IN_NANOS(timeA_p->tv_sec) + timeA_p->tv_nsec) -
        (TT_SECS_IN_NANOS(timeB_p->tv_sec) + timeB_p->tv_nsec);
}
int64_t TimeSpec::getTimeSpecDiffUS(const timespec_t* timeA_p
                                    , const timespec_t* timeB_p)
{
    return ((TT_SECS_IN_NANOS(timeA_p->tv_sec) + timeA_p->tv_nsec) -
        (TT_SECS_IN_NANOS(timeB_p->tv_sec) + timeB_p->tv_nsec))/
        TT_NANOS_PER_MICRO;
}
int64_t TimeSpec::getTimeSpecDiffMS(const timespec_t* timeA_p
                                    , const timespec_t* timeB_p)
{
    return (((timeA_p->tv_sec*TT_NANOS_PER_SEC) + timeA_p->tv_nsec) -
        ((timeB_p->tv_sec*TT_NANOS_PER_SEC) + timeB_p->tv_nsec))/
        TT_NANOS_PER_MILLI;
}
int64_t TimeSpec::getTimeSpecDiffS(const timespec_t* timeA_p
                                   , const timespec_t* timeB_p)
{
    int64_t timeA_NS =  TT_SECS_IN_NANOS(timeA_p->tv_sec) +
        ((int64_t) timeA_p->tv_nsec);

    int64_t timeB_NS =  TT_SECS_IN_NANOS(timeB_p->tv_sec) +
        (static_cast<int64_t>(timeB_p->tv_nsec));

    int64_t diff_NS = (timeA_NS - timeB_NS);
    int64_t diff_S = static_cast<int64_t>(diff_NS/TT_NANOS_PER_SEC);

    return diff_S;
}

} /* TimeSpec */
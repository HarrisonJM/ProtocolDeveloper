/*!
 * @brief Decalarations for the higher precision timeSpec functions
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */

#ifndef PROTOCOLDEVELOPER_TIMESPEC_H
#define PROTOCOLDEVELOPER_TIMESPEC_H

#include <cstdint>
#include <timeTicker/timeTicker.h>
#include "timeTicker/timeTickerCommon.h"

namespace TimeTicker
{

class TimeSpec : public TimeTicker
{
public:
    TimeSpec();
    ~TimeSpec() = default;
    int getClockGetTime(TTTimeClockId clockId
                        , TT_timespec_t* time_p);
    int TimeSubtract(const struct timespec* first_p
                     , const struct timespec* second_p
                     , struct timespec* result_p);
    void TimeAdd(const struct timespec* first_p
                 , const struct timespec* second_p
                 , struct timespec* result_p);
    int64_t TimeDiff(const struct timespec* timeA_p
                     , const struct timespec* timeB_p);
    int64_t TimeDiffNS(const struct timespec* timeA_p
                       , const struct timespec* timeB_p);
    int64_t TimeDiffUS(const struct timespec* timeA_p
                       , const struct timespec* timeB_p);
    int64_t TimeDiffMS(const struct timespec* timeA_p
                       , const struct timespec* timeB_p);
    int64_t TimeDiffS(const struct timespec* timeA_p
                      , const struct timespec* timeB_p);
private:
};
}

#endif /* PROTOCOLDEVELOPER_TIMESPEC_H */

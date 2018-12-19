/*!
 * @brief Common definitions used across the TimeTickerLibrary
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/2018
 */

#ifndef PROTOCOLDEVELOPER_TIMETICKERCOMMON_H
#define PROTOCOLDEVELOPER_TIMETICKERCOMMON_H

#include <ctime>
#include <climits>

//! typedef for the each struct in time/h or sys/time.h
typedef struct timeval timeval_t;
typedef struct timespec timespec_t;
typedef struct tm timeM_t;

typedef enum TTTimeClockId
    : short
{
    /*!
     * This clock represents the realtime clock for the system and corresponds to
     * the amount of time (in seconds and nanoseconds) since the Epoch
     */
        TT_CLOCK_REALTIME = CLOCK_REALTIME,
    /*!
     * This clock represents the non-adjustable clock for the system and
     * corresponds to the amount of time (in seconds and nanoseconds) since some
     * unspecified starting point.
     */
        TT_CLOCK_MONOTONIC = CLOCK_MONOTONIC,
} TTTimeClockId_E;

typedef enum TTRetCode
    : short
{
    TT_RC_FAILURE,
    TT_RC_SUCCESS
} TTRetCode_E;

typedef enum TTCronVars
{
    //! Indicates that this time component is the variable part
        GENTIME_CRON_WILDCARD = (INT_MAX),

    //! Indicates that this time component is not specified
        GENTIME_CRON_NOT_SET = (INT_MAX - 1)
} TTCronVars_E;

typedef struct TTCron
{
    //! The number of seconds after the minute, 0 to 59.
    int second;

    //! The number of minutes after the hour, in the range 0 to 59.
    int minute;

    //! The number of hours past midnight, in the range 0 to 23.
    int hour;

    //! The number of days since Sunday, in the range 0 to 6.
    int dayOfWeek;

    //! The day of the month, in the range 1 to 31.
    int dayOfMonth;

    //! The number of months since January, in the range 0 to 11.
    int month;

    //! The number of years since 1900.
    int year;
} TTCron_t;

/*!
 * \brief Structure to represent an offset from GMT.
 */
typedef struct TTGMTOffset
{
    //! Hour component of the GMT offset
    int hours;

    //! Minute component of the GMT offset
    int minutes;

    //! Entire offset expressed as seconds
    int totalSeconds;
} TTGMTOffset_t;

#endif //PROTOCOLDEVELOPER_TIMETICKERCOMMON_H

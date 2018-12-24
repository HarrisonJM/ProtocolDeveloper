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
typedef struct timeval TT_timeval_t;
typedef struct timespec TT_timespec_t;
typedef struct tm TT_tm_t;

/*!
 * @brief Selects what type of clock we'd like to use (recasts clockid_t from time.h)
 */
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

/*!
 * @brief Handles human readable return codes
 */
typedef enum TTRetCode
    : bool
{
    TT_RC_FAILURE = false,
    TT_RC_SUCCESS = true
} TTRetCode_E;
/*!
 * @brief Structure to represent an offset from GMT.
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

#endif /* PROTOCOLDEVELOPER_TIMETICKERCOMMON_H */

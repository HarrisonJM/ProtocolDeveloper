/*!
 * @brief Holds definitions for the timeTicker class
 *
 * @author hmarcks
 *
 * @addtogroup Time Ticker
 *
 * @date 18/12/2018
 */

#ifndef PROTOCOLDEVELOPER_TIMETICKERDEFINITIONS_H
#define PROTOCOLDEVELOPER_TIMETICKERDEFINITIONS_H

//! Number of seconds in one minute
#define TT_SECS_PER_MIN     60

//! Number of seconds in one hour
#define TT_SECS_PER_HOUR    (60*TT_SECS_PER_MIN)

//! Number of milliseconds in one second
#define TT_MILLIS_PER_SEC   1000

//! Number of milliseconds in one day (1000ms * 60sec * 60mins * 24hours)
#define TT_MILLIS_PER_DAY   86400000

//! Number of microseconds in one second
#define TT_MICROS_PER_SEC   (1000*TT_MILLIS_PER_SEC)

//! Number of nanoseconds in one second
#define TT_NANOS_PER_SEC    (1000*TT_MICROS_PER_SEC)

//! Number of nanoseconds in one millisecond
#define TT_NANOS_PER_MILLI  1000000

//! Number of nanoseconds in one microsecond
#define TT_NANOS_PER_MICRO  1000

/*!
 * @brief String sizes
 * @{
 */
#define TT_TIMEVAL_STR_SIZE (uint8_t)32 //! < YYYY-mm-dd HH:MM:SS.ffffff+0000
#define TT_FRACTION_OFFSET (size_t)20 //! < String offset to the fractional component
#define TT_MAX_FRACTION_SIZE (size_t)6 //! < Number of characters in the fractional component
#define TT_TZ_OFFSET_INDEX (TT_FRACTION_OFFSET+TT_MAX_FRACTION_SIZE) //! < Index of the GMT offset substring
#define TT_NUM_MILISECS_DIGITS (size_t)3 //! < How many 0's are in milliseconds
#define TT_NUM_MICROSECS_DIGITS (size_t)6 //! < How many 0's are in microseconds
/*!@}*/

/*!
 * @brief Returns secs seconds in milliseconds
 */
#define TT_SECS_IN_MILLIS(secs) ((secs) * TT_MILLIS_PER_SEC)

/*!
 * @brief Returns secs seconds in microseconds
 */
#define TT_SECS_IN_MICROS(secs) ((secs) * TT_MICROS_PER_SEC)

/*!
 * @brief Returns secs seconds in nanoseconds
 */
#define TT_SECS_IN_NANOS(secs) ((secs) * TT_NANOS_PER_SEC)

/*!
 * @brief Maximum value for the time_t data type.
 */
#define TT_TIME_MAX ((time_t) LONG_MAX)

#endif //PROTOCOLDEVELOPER_TIMETICKERDEFINITIONS_H

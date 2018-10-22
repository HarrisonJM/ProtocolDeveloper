/*!
\verbatim
Nokia Networks
Directory Server
(C) 2007 by Nokia Solutions and Networks
\endverbatim

\date 28 Feb 2007

\author Andy Langrick 

\brief Time related functions.

\ingroup GEN
*/
#ifndef APTOGEN_BASE_GENTIME_H_
#define APTOGEN_BASE_GENTIME_H_

/*
 * System header files
 */
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

/*
 * NDS header files
 */
#include <genRetCode.h>


//! Number of seconds in one minute
#define GENTIME_SECS_PER_MIN     60

//! Number of seconds in one hour
#define GENTIME_SECS_PER_HOUR    (60*GENTIME_SECS_PER_MIN)

//! Number of milliseconds in one second
#define GENTIME_MILLIS_PER_SEC   1000

//! Number of milliseconds in one day (1000ms * 60sec * 60mins * 24hours)
#define GENTIME_MILLIS_PER_DAY   86400000

//! Number of microseconds in one second
#define GENTIME_MICROS_PER_SEC   (1000*GENTIME_MILLIS_PER_SEC)

//! Number of nanoseconds in one second
#define GENTIME_NANOS_PER_SEC    (1000*GENTIME_MICROS_PER_SEC)

//! Number of nanoseconds in one millisecond
#define GENTIME_NANOS_PER_MILLI  1000000

//! Number of nanoseconds in one microsecond
#define GENTIME_NANOS_PER_MICRO  1000

/*!
 * \brief Returns secs seconds in milliseconds
 */
#define GENTIME_SECS_IN_MILLIS(secs) ((secs) * GENTIME_MILLIS_PER_SEC)

/*!
 * \brief Returns secs seconds in microseconds
 */
#define GENTIME_SECS_IN_MICROS(secs) ((secs) * GENTIME_MICROS_PER_SEC)

/*!
 * \brief Returns secs seconds in nanoseconds
 */
#define GENTIME_SECS_IN_NANOS(secs) ((secs) * GENTIME_NANOS_PER_SEC)

/*!
 * \brief Maximum value for the time_t data type.
 */
#define GENTIME_TIME_MAX ((time_t) LONG_MAX)

enum GenTimeCronVars
{
  //! Indicates that this time component is the variable part
  GENTIME_CRON_WILDCARD = (INT_MAX),

  //! Indicates that this time component is not specified
  GENTIME_CRON_NOT_SET = (INT_MAX - 1)
};

/*!
 * \brief Structure to specify a crontab like schedule.
 *
 * \par Each field should be given a valid value for its calendar type or set to
 * either ::GENTIME_CRON_WILDCARD or ::GENTIME_CRON_NOT_SET.
 *
 * \par When the fields are considered in order from second to year, once one of
 * the enum GenTimeCronVars values has been used, all following fields should
 * be set to ::GENTIME_CRON_NOT_SET.
 *
 * \par For example { .second=0, .minute=30, .hour=GENTIME_CRON_WILDCARD }
 * specifies that the event occurs once every hour, at 30 minutes and 0 seconds
 * past the hour.
 */
struct GenTimeCron
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
};

/*!
 * \brief Structure to represent an offset from GMT.
 */
struct GenTimeGMTOffset
{
  //! Hour component of the GMT offset
  int hours;

  //! Minute component of the GMT offset
  int minutes;

  //! Entire offset expressed as seconds
  int totalSeconds;
};

/*!
 * \brief Clock types supported by GenTime.
 */
typedef enum GenTimeClockId
{
  /*!
   * This clock represents the realtime clock for the system and corresponds to
   * the amount of time (in seconds and nanoseconds) since the Epoch
   */
  GENTIME_CLOCK_REALTIME = CLOCK_REALTIME,

  /*!
   * This clock represents the non-adjustable clock for the system and
   * corresponds to the amount of time (in seconds and nanoseconds) since some
   * unspecified starting point.
   */
  GENTIME_CLOCK_MONOTONIC = CLOCK_MONOTONIC,
} GenTimeClockId;

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/*!
 * \brief Returns the value of the Read TimeStamp Count (RDTSC) instruction.
 */
uint64_t genRdtsc(void);

/*!
 * \brief Retrieve the GMT Offset from the specified struct tm.
 */
extern int genGetGMTOffset(const struct tm *tm_p,
                           struct GenTimeGMTOffset *offset_p);

/*!
 * \brief Print the GMT offset without a NULL terminator into the specified
 * buffer.
 */
int genPrintGMTOffset(const struct tm *theTimeTM_p,
                      char *buffer_p,
                      size_t length);

#define GENERALIZED_TIME_STRING_LENGTH  64

extern GenReturnCode genPrintGeneralizedTime(const struct tm *tm_p,
                                             unsigned int *microsecs_p,
                                             unsigned int fractionDigits,
                                             char *buf_p,
                                             size_t bufSize);

/*
 * \brief Returns a String containing a timestamp for the current time.
 *        Uses microseconds resolution
 */
extern const char *genTimestamp(void);

// As above, but only millisecond resolution
extern const char *genTimestampMilli();

#define GEN_XML_TS_DATE 1
#define GEN_XML_TS_TIME 2
#define GEN_XML_TS_DATETIME (GEN_XML_TS_DATE | GEN_XML_TS_TIME)
char *genXMLTimestamp(time_t t, int components);

/*!
 * \brief Returns a string representation of the specified struct timeval in
 * the format "%Y-%m-%d %H:%M:%S.ffffff"
 */
extern const char *genTimevalToString(const struct timeval *tv);

/*!
 * \brief Returns a string representation of the specified struct timespec in
 * the format "%Y-%m-%d %H:%M:%S.fffffffff"
 */
extern const char *genTimespecToString(const struct timespec *time_p);

/*!
 * \brief Returns a human readable string representation
 */
extern const char *genTimeToString(time_t time);

/*!
 * \brief Subtracts the second struct timespec from the first struct timespec,
 * storing the result in result_p.
 */
extern int genTimevalSubtract(const struct timespec *first_p,
                              const struct timespec *second_p,
                              struct timespec *result_p);

/*!
 * \brief Computes the sum of the two specified struct timespec objects,
 * returning the result in result_p.
 */
extern void genTimespecAdd(const struct timespec *first_p,
                           const struct timespec *second_p,
                           struct timespec *result_p);

/*
 * \brief Returns the difference between the two struct timespec objects.
 */
extern int64_t genTimespecDiff(const struct timespec *timeA_p,
                               const struct timespec *timeB_p);

/*
 * \brief Returns the difference between the two struct timespec objects nano
 * seconds.
 */
extern int64_t genTimespecDiffNS(const struct timespec *timeA_p,
                                 const struct timespec *timeB_p);

/*
 * \brief Returns the difference between the two struct timespec objects in
 * microseconds.
 */
extern int64_t genTimespecDiffUS(const struct timespec *timeA_p,
                                 const struct timespec *timeB_p);

/*
 * \brief Returns the difference between the two struct timespec objects in
 * milliseconds.
 */
extern int64_t genTimespecDiffMS(const struct timespec *timeA_p,
                                 const struct timespec *timeB_p);

/*
 * \brief Returns the difference between the two struct timespec objects in
 * seconds.
 */
extern int64_t genTimespecDiffS(const struct timespec *timeA_p,
                                const struct timespec *timeB_p);

/*!
 * \brief Returns the time of the specified clock clockId.
 */
extern int genClockGetTime(GenTimeClockId clockId, struct timespec *time_p);

#endif /* APTOGEN_BASE_GENTIME_H_ */

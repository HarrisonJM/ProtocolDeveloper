/*!
 * \brief Time related functions.
 *
 * \ingroup GEN
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <regex.h>
#include <errno.h>

#include <genTime.h>
#include <genTimePrivate.h>

#include "testsuite/TestSuite.h"

static const size_t NUM_MICROSECS_DIGITS = 6;

static const char *_genTimevalToString(const struct timeval *tv,
                                       size_t numDecimalDigits,
                                       char timestampBuffer[],
                                       struct timeval &lastTimeTV,
                                       int &lastHour);

/*!
 * \brief Retrieve the GMT Offset from the specified struct tm.
 *
 * \param[in] tm_p  Time.
 *
 * \param[out] offset_p  Pointer to a struct GenTimeGMTOffset which is
 *                       updated with the GMT offset information.
 */
int genGetGMTOffset(const struct tm *tm_p,
                    struct GenTimeGMTOffset *offset_p)
{
  if (!tm_p)
  {
    return -1;
  }

  if (!offset_p)
  {
    return -1;
  }

  offset_p->hours = 0;
  offset_p->minutes = 0;
  offset_p->totalSeconds = 0;

#ifdef _BSD_SOURCE
  offset_p->minutes = (tm_p->tm_gmtoff % 3600)/60;
  offset_p->hours = (tm_p->tm_gmtoff/3600);
#else
  offset_p->minutes = (tm_p->__tm_gmtoff % 3600)/60;
  offset_p->hours = (tm_p->__tm_gmtoff/3600);
#endif

  offset_p->totalSeconds = (offset_p->hours * GENTIME_SECS_PER_HOUR) +
                           (offset_p->minutes * GENTIME_SECS_PER_MIN);

  return 0;
}

/*!
 * \brief Print the GMT offset plus NULL terminator into the specified buffer.
 *
 * At most 6 bytes of buffer are required.
 *
 * \param[in] theTimeTM_p  struct tm containing the broken-down time value.
 *
 * \param[out] buffer_p  Buffer into which the GMT offset is printed.
 *
 * \param[in] length  Number of bytes available in buffer_p.
 *
 * \return The number of characters printed not including the trailing '\0'.
 */
int genPrintGMTOffset(const struct tm *theTimeTM_p,
                      char *buffer_p,
                      size_t length)
{
  int gmtOffset, hours, minutes, numPrinted;

  // Get the offset
#ifdef _BSD_SOURCE
  gmtOffset = theTimeTM_p->tm_gmtoff;
#else
  gmtOffset = theTimeTM_p->__tm_gmtoff;
#endif

  if (0 == gmtOffset)
  {
    numPrinted = snprintf(buffer_p, length, "Z");
  }
  else
  {
    char sign = (gmtOffset > 0) ? '+' : '-';
    gmtOffset = abs(gmtOffset);
    ldiv_t result = ldiv(gmtOffset, GENTIME_SECS_PER_HOUR);
    hours = result.quot;
    minutes = result.rem / GENTIME_SECS_PER_MIN;
    numPrinted = snprintf(buffer_p,
                          length,
                          "%c%02d%02d",
                          sign,
                          hours,
                          minutes);
  }

  return numPrinted;
}

/*
 * \brief Returns a String containing a timestamp for the current time.
 *
 * The timestamp is in the format YYYY-MM-DD HH:MM:SS.FFFFFF[(+|-HHMM)|Z], where:
 *
 * YYYY   - The year as a 4 digit decimal number including the century.
 * MM     - The month as a decimal number (range 01 to 12).
 * DD     - The day of the month as a decimal number (range 01 to 31).
 * HH     - The hour as a decimal number using a 24-hour clock (range 00 to 23)
 * MM     - The minute as a decimal number (range 00 to 59).
 * SS     - The second as a decimal number (range 00 to 60 [leap seconds]).
 * FFFFFF - The microseconds as a 6 digit decimal number
 *
 * The return value points to a statically allocated buffer which might be
 * overwritten by subsequent calls to this function.
 *
 * \return Pointer to a statically allocated buffer containing the timestamp.
 */
const char *genTimestamp()
{
  static char timestampBuffer[GEN_TIMEVAL_STR_SIZE];
  static struct timeval lastTime = {0};
  static int lastHour = -1;

  // Get the current time (seconds, microseconds)
  struct timeval theTimeTV = {0};
  (void) gettimeofday(&theTimeTV, NULL);

  return _genTimevalToString(&theTimeTV, NUM_MICROSECS_DIGITS,
                             timestampBuffer,
                             lastTime, lastHour);
}

/*
 * \brief Returns a String containing a timestamp for the current time.
 *
 * The timestamp is in the format YYYY-MM-DD HH:MM:SS.FFF[(+|-HHMM)|Z], where:
 *
 * YYYY   - The year as a 4 digit decimal number including the century.
 * MM     - The month as a decimal number (range 01 to 12).
 * DD     - The day of the month as a decimal number (range 01 to 31).
 * HH     - The hour as a decimal number using a 24-hour clock (range 00 to 23)
 * MM     - The minute as a decimal number (range 00 to 59).
 * SS     - The second as a decimal number (range 00 to 60 [leap seconds]).
 * FFF    - The milliseconds as a 3 digit decimal number
 *
 * The return value points to a statically allocated buffer which might be
 * overwritten by subsequent calls to this function.
 *
 * \return Pointer to a statically allocated buffer containing the timestamp.
 */
const char *genTimestampMilli()
{
  static char timestampBuffer[GEN_TIMEVAL_STR_SIZE];
  static struct timeval lastTime = {0};
  static int lastHour = -1;

  // Get the current time (seconds, microseconds)
  struct timeval theTimeTV = {0};
  (void) gettimeofday(&theTimeTV, NULL);

  const size_t NUM_MILLISECS_DIGITS = 3;

  return _genTimevalToString(&theTimeTV, NUM_MILLISECS_DIGITS, timestampBuffer, lastTime, lastHour);
}

/*!
 * \brief Prints the time specified by the tm_p argument into the buffer in
 * GeneralizedTime format.
 *
 * GeneralizedTime format is specified by RFC 4517 section 3.3.13.
 *
 * YYYYMMDDHHMMSS[.fff][Z|[+-]hhmm]
 *
 * \param[in] tm_p  Time to be printed.
 *
 * \param[in] microsecs_p Optional microseconds
 *
 * \param[in] fractionDigits Number of fractional digits to print, 0-6
 *
 * \param[out] buf_p  Buffer into which the GeneralizedTime string will be printed.
 *
 * \param[in] bufSize  Size of the buffer buf_p.
 *
 * \return Zero on success, non-zero on error.
 */
GenReturnCode genPrintGeneralizedTime(const struct tm *tm_p,
                                      unsigned int *microsecs_p,
                                      unsigned int fractionDigits,
                                      char *buf_p,
                                      size_t bufSize)
{
  if (!tm_p)
  {
    return GEN_RC_FAILURE;
  }

  if (!buf_p)
  {
    return GEN_RC_FAILURE;
  }

  if (fractionDigits > 6)
  {
    return GEN_RC_FAILURE;
  }

  // Get the GMT offset from the input time
  struct GenTimeGMTOffset gmtOffset = {0};

  if (genGetGMTOffset(tm_p, &gmtOffset))
  {
    return GEN_RC_FAILURE;
  }

  // Print the struct tm into the buffer
  int numPrinted = strftime(buf_p, bufSize, "%Y%m%d%H%M%S", tm_p);

  if (numPrinted <= 0)
  {
    return GEN_RC_FAILURE;
  }

  // Remaining buffer size is reduced
  bufSize -= numPrinted;
  buf_p += numPrinted;

  // Print the optional microseconds component
  if (microsecs_p && fractionDigits)
  {
    char microStr[10];
    snprintf(microStr, sizeof(microStr), "%06d", *microsecs_p);

    numPrinted = snprintf(buf_p,
                          bufSize,
                          ".%.*s",
                          fractionDigits,
                          microStr);

    // snprintf output was truncated, return error
    if (numPrinted >= (int)bufSize)
    {
      return GEN_RC_FAILURE;
    }
    // snprintf output error, return error
    else if (numPrinted < 0)
    {
      return GEN_RC_FAILURE;
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

    numPrinted = snprintf(buf_p,
                          bufSize,
                          "%c%02d%02d",
                          offsetSign,
                          gmtOffHour,
                          gmtOffMins);
  }
  else
  {
    numPrinted = snprintf(buf_p,
                          bufSize,
                          "%c",
                          'Z');
  }

  // snprintf output was truncated, return error
  if (numPrinted >= (int)bufSize)
  {
    return GEN_RC_FAILURE;
  }
  // snprintf output error, return error
  else  if (numPrinted < 0)
  {
    return GEN_RC_FAILURE;
  }
  else
  {
    return GEN_RC_SUCCESS;
  }
}

/*!
 * \brief Format a unix time as XML date/time stamp
 *
 * \param[in] t Time
 *
 * \param[in] components
 *    - GEN_XML_TS_DATE Format a date
 *    - GEN_XML_TS_TIME Format a time
 *    - GEN_XML_TS_DATETIME Format a date and time stamp
 *
 * \return
 *    Formated date/time stamp on success
 *    NULL on error
 */
char *genXMLTimestamp(time_t t, int components)
{
  static char datetimestamp[GEN_XML_TS_DATETIME_LEN + 1] = {0,};
  static char datestamp[GEN_XML_TS_DATE_LEN + 1] = {0,};
  static char timestamp[GEN_XML_TS_TIME_LEN + 1] = {0,};
  struct tm *timeinfo;
  size_t len;
  char *ret = NULL;

  timeinfo = localtime (&t);

  if (components & GEN_XML_TS_DATE)
  {
    len = strftime (datestamp, sizeof (datestamp), "%Y-%m-%d", timeinfo);
    if (len == 0)
    {
      return NULL;
    }

    ret = datestamp;
  }

  if (components & GEN_XML_TS_TIME)
  {
    len = strftime (timestamp, sizeof (timestamp), "%H:%M:%S%z", timeinfo);
    if (len == 0)
    {
      return NULL;
    }

    // The format string above will output the timezone as
    // +0000, however xml requires there to be a colon
    // present (eg. +00:00).
    timestamp[13] = timestamp[12];
    timestamp[12] = timestamp[11];
    timestamp[11] = ':';

    ret = timestamp;
  }

  if (components == GEN_XML_TS_DATETIME)
  {
    // Build full date time stamp
    strncpy (&datetimestamp[GEN_XML_TS_DATE_START], datestamp, GEN_XML_TS_DATE_LEN);
    datetimestamp[GEN_XML_TS_SEPARATOR] = 'T';
    strncpy (&datetimestamp[GEN_XML_TS_TIME_START], timestamp, GEN_XML_TS_TIME_LEN);

    ret = datetimestamp;
  }

  return ret;
}

/*!
 * \brief Returns a string representation of the specified struct timeval in
 * the format "%Y-%m-%d %H:%M:%S.ffffff"
 *
 * \param tv  The time.
 *
 * \return String containing the presented time or the empty string on error.
 */
const char *genTimevalToString(const struct timeval *tv)
{
  static char timestampBuffer[GEN_TIMEVAL_STR_SIZE];
  static struct timeval lastTime = {0};
  static int lastHour = -1;

  return _genTimevalToString(tv, NUM_MICROSECS_DIGITS, timestampBuffer, lastTime, lastHour);
}

/*!
 * \brief Returns a string representation of the specified struct timeval in
 * the format "%Y-%m-%d %H:%M:%S.f{numDecimalDigits}"
 *
 * \param[in] tv The time to present
 * \param[in] numDecimalDigits Number of decimal digits to include in fraction component (up to 6)
 * \param[in,out] timestampBuffer Buffer in which to build string, size GEN_TIMEVAL_STR_SIZE. Must be re-used between calls.
 * \param[in,out] lastTimeTV Last time this function was called. Used for caching in timestampBuffer
 * \param[in,out] lastHour Cached value for last timestamp hour, avoids re-calculating GMT offset
 *
 * \return String containing the presented time or the empty string on error.
 */
static const char *_genTimevalToString(const struct timeval *tv,
                                       size_t numDecimalDigits,
                                       char timestampBuffer[],
                                       struct timeval &lastTimeTV,
                                       int &lastHour)
{
  // String offset to the fractional component
  static const size_t FRACTION_OFFSET = 20;

  // Maximum number of characters in the fractional component
  static const size_t MAX_FRACTION_SIZE = 6;

  // Index of the GMT offset substring
  const size_t tzOffsetIndex = FRACTION_OFFSET + numDecimalDigits;

  /*
   * localtime_v and strftime are time consuming. Only bother to do them if the
   * second is different to the last time we got called.
   * If the second is the same then we just need to print the milliseconds.
   */
  if (lastTimeTV.tv_sec != tv->tv_sec)
  {
    lastTimeTV.tv_sec = tv->tv_sec;

    // Convert UTC time to broken-time struct tm
    time_t secs = (time_t) tv->tv_sec;
    struct tm theTimeTM;
    tzset();
    struct tm *theTimeTM_p = localtime_r(&secs, &theTimeTM);

    if (!theTimeTM_p)
    {
      return "";
    }

    // Print the time fields into the buffer
    (void) strftime(timestampBuffer,
                    GEN_TIMEVAL_STR_SIZE,
                    "%Y-%m-%d %H:%M:%S.",
                    theTimeTM_p);

    /*
     * Re-generate the GMT offset every hour
     */
    if (lastHour != theTimeTM_p->tm_hour)
    {
      lastHour = theTimeTM_p->tm_hour;
      genPrintGMTOffset(theTimeTM_p,
                        timestampBuffer + tzOffsetIndex,
                        GEN_TIMEVAL_STR_SIZE - tzOffsetIndex);
    }
  }

  // print the fractional component
  {
    char fractionBuffer[MAX_FRACTION_SIZE + 1];

    (void) snprintf(fractionBuffer,
                    sizeof(fractionBuffer),
                    "%06u",
                    (unsigned int) (tv->tv_usec));

    // Only copy the number of digits requested
    memcpy(timestampBuffer + FRACTION_OFFSET, fractionBuffer, numDecimalDigits);
  }

  return timestampBuffer;
}

/*!
 * \brief Returns a string representation of the specified struct timespec in
 * the format "%Y-%m-%d %H:%M:%S.ffffff" (microseconds precision)
 *
 * \param time_p  The time.
 *
 * \return a string representation of the specified struct timespec.
 */
const char *genTimespecToString(const struct timespec *time_p)
{
  static char timestampBuffer[100];
  static struct timespec lastTime = {0};

  // String offset to the fractional component
  static const size_t FRACTION_OFFSET = 20;

  // Number of characters in the fractional component
  static const size_t FRACTION_SIZE = 6;

  // Index of the GMT offset substring
  static const size_t TZ_OFFSET_INDEX = FRACTION_OFFSET + FRACTION_SIZE;

  if (!time_p)
  {
    return "";
  }

  /*
   * localtime_v and strftime are time consuming. Only bother to do them if the
   * second is different to the last time we got called.
   * If the second is the same then we just need to print the nanoseconds.
   */
  if (lastTime.tv_sec != time_p->tv_sec)
  {
    lastTime.tv_sec = time_p->tv_sec;

    // Convert UTC time to broken-time struct tm
    time_t secs = (time_t) time_p->tv_sec;
    struct tm theTimeTM;
    tzset();
    struct tm *theTimeTM_p = localtime_r(&secs, &theTimeTM);

    if (!theTimeTM_p)
    {
      return "";
    }

    // Print the time fields into the buffer
    (void) strftime(timestampBuffer,
                    sizeof(timestampBuffer),
                    "%Y-%m-%d %H:%M:%S.",
                    theTimeTM_p);

    /*
     * Re-generate the GMT offset every hour
     */
    static int lastHour = -1;

    if (lastHour != theTimeTM_p->tm_hour)
    {
      lastHour = theTimeTM_p->tm_hour;
      genPrintGMTOffset(theTimeTM_p,
                        timestampBuffer + TZ_OFFSET_INDEX,
                        sizeof(timestampBuffer) - TZ_OFFSET_INDEX);
    }
  }

  // print the fractional component, truncating to microseconds
  {
    char fractionBuffer[FRACTION_SIZE + 1];

    (void) snprintf(fractionBuffer,
                    sizeof(fractionBuffer),
                    "%09lu",
                    time_p->tv_nsec);

    memcpy(timestampBuffer + FRACTION_OFFSET, fractionBuffer, FRACTION_SIZE);
  }

  return timestampBuffer;
}

/*
 * \brief Returns the difference between the two struct timespec objects nano
 * seconds.
 *
 * Computes the result of timeA_p - timeB_p in nanoseconds.
 *
 * \param timeA_p  The first time.
 *
 * \param timeB_p  The second time.
 *
 * \return the result of timeA_p - timeB_p in nano-seconds.
 */
int64_t genTimespecDiffNS(const struct timespec *timeA_p, const struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * GENTIME_NANOS_PER_SEC) + timeA_p->tv_nsec) -
         ((timeB_p->tv_sec * GENTIME_NANOS_PER_SEC) + timeB_p->tv_nsec);
}

/*
 * \brief Returns the difference between the two struct timespec objects in
 * microseconds.
 *
 * Computes the result of timeA_p - timeB_p in microseconds.
 *
 * \param timeA_p  The first time.
 *
 * \param timeB_p  The second time.
 *
 * \return the result of timeA_p - timeB_p in microseconds.
 */
int64_t genTimespecDiffUS(const struct timespec *timeA_p, const struct timespec *timeB_p)
{
  return (((timeA_p->tv_sec * GENTIME_NANOS_PER_SEC) + timeA_p->tv_nsec) -
          ((timeB_p->tv_sec * GENTIME_NANOS_PER_SEC) + timeB_p->tv_nsec)) /
         GENTIME_NANOS_PER_MICRO;
}

/*
 * \brief Returns the difference between the two struct timespec objects in
 * milliseconds.
 *
 * Computes the result of timeA_p - timeB_p in milliseconds.
 *
 * \param timeA_p  The first time.
 *
 * \param timeB_p  The second time.
 *
 * \return the result of timeA_p - timeB_p in milliseconds.
 */
int64_t genTimespecDiffMS(const struct timespec *timeA_p, const struct timespec *timeB_p)
{
  return (((timeA_p->tv_sec * GENTIME_NANOS_PER_SEC) + timeA_p->tv_nsec) -
          ((timeB_p->tv_sec * GENTIME_NANOS_PER_SEC) + timeB_p->tv_nsec)) /
         GENTIME_NANOS_PER_MILLI;
}

/*
 * \brief Returns the difference between the two struct timespec objects in
 * whole seconds.
 *
 * Computes the result of timeA_p - timeB_p in seconds, any fractional part
 * is truncated.
 *
 * \param timeA_p  The first time.
 *
 * \param timeB_p  The second time.
 *
 * \return the result of timeA_p - timeB_p in seconds.
 */
int64_t genTimespecDiffS(const struct timespec *timeA_p, const struct timespec *timeB_p)
{
  int64_t timeA_NS = ((int64_t) timeA_p->tv_sec * (int64_t) GENTIME_NANOS_PER_SEC) +
                     ((int64_t) timeA_p->tv_nsec);

  int64_t timeB_NS = ((int64_t) timeB_p->tv_sec * (int64_t) GENTIME_NANOS_PER_SEC) +
                     ((int64_t) timeB_p->tv_nsec);

  int64_t diff_NS = (timeA_NS - timeB_NS);
  int64_t diff_S = (int64_t) (diff_NS / GENTIME_NANOS_PER_SEC);

  return diff_S;
}

/*!
 * \brief Subtracts the second struct timespec from the first struct timespec,
 * storing the result in result_p.
 *
 * \see http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
 *
 * \param first_p [input] The first struct timespec
 *
 * \param second_p [input] The second struct timespec
 *
 * \param result_p [output] Pointer to a struct timespec in which to store the
 * result.
 *
 * \return TRUE if result is negative, otherwise FALSE.
 */
int genTimevalSubtract(const struct timespec *first_p,
                       const struct timespec *second_p,
                       struct timespec *result_p)
{
  struct timespec localFirst, localSecond;
  const long int NUM_NANO_SECS = 1000000000;

  // Copy first_p and second_p
  localFirst = *first_p;
  localSecond = *second_p;

  // Perform the carry for the later subtraction by updating y.
  if (localFirst.tv_nsec < localSecond.tv_nsec)
  {
    uint64_t nsec = (localSecond.tv_nsec - localFirst.tv_nsec) / NUM_NANO_SECS + 1;
    localSecond.tv_nsec -= NUM_NANO_SECS * nsec;
    localSecond.tv_sec += nsec;
  }

  if (localFirst.tv_nsec - localSecond.tv_nsec > NUM_NANO_SECS)
  {
    uint64_t nsec = (localFirst.tv_nsec - localSecond.tv_nsec) / NUM_NANO_SECS;
    localSecond.tv_nsec += 1000000 * nsec;
    localSecond.tv_sec -= nsec;
  }

  /* Compute the time remaining to wait. tv_usec  is certainly positive. */
  result_p->tv_sec = localFirst.tv_sec - localSecond.tv_sec;
  result_p->tv_nsec = localFirst.tv_nsec - localSecond.tv_nsec;

  /* Return 1 if result is negative. */
  return localFirst.tv_sec < localSecond.tv_sec;
}

/*!
 * \brief Computes the sum of the two specified struct timespec objects,
 * returning the result in result_p.
 *
 * \param first_p  The first struct timespec.
 *
 * \param second_p  The second struct timespec.
 *
 * \param result_p  [output] Pointer to a struct timespec into which the
 * result is written.
 */
void genTimespecAdd(const struct timespec *first_p,
                    const struct timespec *second_p,
                    struct timespec *result_p)
{
  result_p->tv_sec = first_p->tv_sec + second_p->tv_sec;

  uint64_t nanos = first_p->tv_nsec + second_p->tv_nsec;

  if (nanos > GENTIME_NANOS_PER_SEC)
  {
    result_p->tv_nsec = nanos - GENTIME_NANOS_PER_SEC;
    result_p->tv_sec += 1;
  }
  else
  {
    result_p->tv_nsec = nanos;
  }
}

/*
 * \brief Returns the difference between the two struct timespec objects.
 *
 * Computes the result of timeA_p - timeB_p, returning the value in nano
 * seconds.
 *
 * \param timeA_p  The first time.
 *
 * \param timeB_p  The second time.
 *
 * \return the result of timeA_p - timeB_p in nano-seconds.
 */
int64_t genTimespecDiff(const struct timespec *timeA_p, const struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
         ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

/*!
 * \brief Returns a string representation of the specified time in the format
 * "%Y-%m-%d %H:%M:%S"
 *
 * Not thread safe.
 */
const char *genTimeToString(time_t theTime)
{
  static char timestampBuffer[32];
  struct tm theTimeTM = {0};

  tzset();
  (void) localtime_r(&theTime, &theTimeTM);

  // Print the time fields into the buffer
  size_t result = strftime(timestampBuffer,
                           sizeof(timestampBuffer),
                           "%Y-%m-%d %H:%M:%S",
                           &theTimeTM);

  if (result > 0)
  {
    return timestampBuffer;
  }
  else
  {
    return NULL;
  }
}

/*!
 * \brief Returns the time of the specified clock clockId.
 *
 * \param[in] clockId  The clock type.
 *
 * \param[out] time_p  Pointer to a struct timespec into which the time is
 * copied.
 *
 * \return 0 for success, -1 for failure (errno is set appropriately).
 */
int genClockGetTime(GenTimeClockId clockId, struct timespec *time_p)
{
  return clock_gettime(clockId, time_p);
}

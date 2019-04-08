/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 18/12/18
 */

#include <ctime>
#include <timeTicker/timeTickerCommon.h>
#include <cstring>
#include "xMLTime.h"

namespace timeTicker
{

XMLTime::XMLTime()
{
}

char* XMLTime::getXMLTimestamp(time_t t
                               , int components)
{
    //! @TODO Finish classifying
    static char dateTimeStamp[TT_XML_TS_DATETIME_LEN + 1] = {0};
    static char dateStamp[TT_XML_TS_DATE_LEN + 1] = {0};
    static char timeStamp[TT_XML_TS_TIME_LEN + 1] = {0};

    TT_tm_t* timeInfo;
    size_t len;
    char* ret = nullptr;

    timeInfo = localtime(&t);

    if (components & TT_XML_TS_DATE_START)
    {
        len = std::strftime(dateStamp
                            , sizeof(dateStamp)
                            , "%Y-%m-%d"
                            , timeInfo);
        if (len == 0)
        {
            return nullptr;
        }

        ret = dateStamp;
    }

    if (components & TT_XML_TS_TIME_START)
    {
        len = std::strftime(timeStamp
                            , sizeof(timeStamp)
                            , "%H:%M:%S%z"
                            , timeInfo);
        if (len == 0)
        {
            return nullptr;
        }

        // The format string above will output the timezone as
        // +0000, however xml requires there to be a colon
        // present (eg. +00:00).
        timeStamp[13] = timeStamp[12];
        timeStamp[12] = timeStamp[11];
        timeStamp[11] = ':';

        ret = timeStamp;
    }

    if (components == TT_XML_TS_DATETIME_LEN)
    {
        // Build full date time stamp
        std::strncpy(&dateTimeStamp[TT_XML_TS_DATE_START]
                     , dateStamp
                     , TT_XML_TS_DATE_LEN);
        dateTimeStamp[TT_XML_TS_SEPARATOR] = 'T';
        std::strncpy(&dateTimeStamp[TT_XML_TS_TIME_START]
                     , timeStamp
                     , TT_XML_TS_TIME_LEN);

        ret = dateTimeStamp;
    }

    return ret;
}
} /* timeTicker */
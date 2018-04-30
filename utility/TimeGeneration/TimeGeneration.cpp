/*!
 * @brief TimeGeneration Class
 *
 * This class is to do with time generation and time keeping
 * It'll track uptime and return the current date/time
 *
 * @addtogroup Utility
 *
 * @date March 2018
 */
#include "TimeGeneration.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Utility
{
    static struct tm getTimeStruct()
    {
        time_t timer;
        struct tm *timeinfo;
        timeinfo = localtime(&timer);

        return *timeinfo;
    }

    /*!
     * @brief constructor
     */
    TimeGeneration::TimeGeneration() :
        startDate([](void) -> struct tm { return getTimeStruct(); }() )
    {

    }

    //----------------------------------------------------------------------

    TimeGeneration::~TimeGeneration(){}

    //----------------------------------------------------------------------

    std::string TimeGeneration::getUpTimeStamp()
    {
        return std::string("24:00:1.123456");
    }

    //----------------------------------------------------------------------

    long long TimeGeneration::getUpTimeMicS()
    {
        return 356401123456;
    }

    //----------------------------------------------------------------------

    std::string TimeGeneration::getCurrentTimeStamp()
    {
        return std::string("30/04/18 20:30:50.123456");
    }

    //----------------------------------------------------------------------

    long long TimeGeneration::getCurrentTimeMicS()
    {
        return 1525120244000;
    }

} /* Namespace */

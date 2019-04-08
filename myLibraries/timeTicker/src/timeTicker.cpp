/*!
 * @brief Implementation for the TimeTicker Base Class
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */

#include <timeTicker/timeTicker.h>

#include "timeTicker/timeTicker.h"

namespace timeTicker
{

TimeTicker::TimeTicker()
{

}

const char* TimeTicker::getTimeStampMicro()
{
    return "Don't use the base class(seconds)";
}
const char* TimeTicker::getTimestampMilli()
{
    return "Don't use the base class(milliseconds)";
}
const char* TimeTicker::getStringMicro(const struct timeval* tv)
{
    return "Don't use the base class (string)";
}
} /* namespace timeTicker */
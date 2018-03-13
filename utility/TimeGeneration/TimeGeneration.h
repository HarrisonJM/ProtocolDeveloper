/*!
 * @brief Functions related to timeGeneration
 *
 *  @addtogroup Utility
 *
 *  @date March 2018
 */
#ifndef PROTOCOLDEVELOPER_TIMEGENERATION_H
#define PROTOCOLDEVELOPER_TIMEGENERATION_H

#include <string>

namespace Utility
{
    class TimeGeneration
    {
        TimeGeneration();
        ~TimeGeneration();

        std::string GenerateCurrentDate();
        std::string GenerateTimeStamp();
        std::string GenerateCurrentTimeString();
    };

}

#endif /* PROTOCOLDEVELOPER_TIMEGENERATION_H */
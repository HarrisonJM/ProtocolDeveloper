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
    /*!
     * @brief Keeps time across the system
     *
     * Will act as a singleton across the system that
     * will be used to keep and track time
     *
     * @todo needs more work
     */
    class TimeGeneration
    {
        //! Constructor
        TimeGeneration();
        //! Denstructor
        ~TimeGeneration();

        //! calculates the current date and returns a string
        std::string GenerateCurrentDate();
        //! Generates a time stamp to return
        std::string GenerateTimeStamp();
        //! Calculates the current time as a string
        std::string GenerateCurrentTimeString();
    };

}

#endif /* PROTOCOLDEVELOPER_TIMEGENERATION_H */
/*!
 * \brief TimeGeneration Class
 *
 * This class is to do with time generation and formatting with in the program
 *
 * @addtogroup Utility
 *
 * @date March 2018
 */
#include "TimeGeneration.h"
#include <sstream>
#include <iostream>

namespace Utility
{
    TimeGeneration::TimeGeneration(){}
    TimeGeneration::~TimeGeneration(){}

    /*!
     * @brief GenerateCurrentTimeString
     *
     * Returns the current time as a string
     *
     * @return The current time as a string
     */
    std::string TimeGeneration::GenerateCurrentTimeString()
    {
        //! @todo This
        return "16:04:59.999999";
    }

    /*!
     * @brief GenerateCurrentDate
     *
     * Returns the current date as a string
     *
     * @return The current date as a string
     */
    std::string TimeGeneration::GenerateCurrentDate()
    {
        //! @todo This
        return "07/12/2017";
    }

    /*!
     * @brief GenerateTimeStamp
     *
     * Generates a time and date stampa dn returns ti as a string
     *
     *  @return A string that contains the current date and time
     */
    std::string TimeGeneration::GenerateTimeStamp()
    {
        std::stringstream timeStamp;
        timeStamp << '[' << GenerateCurrentTimeString()
            << "]["
            << GenerateCurrentDate()
            << ']';

        return timeStamp.str();
    }
}

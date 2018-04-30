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
#include <ctime>
#include <sys/time.h>

namespace Utility
{
    //! High resolution typedef
    //typedef std::chrono::time_point<std::chrono::high_resolution_clock> hrClock_t;

    /*!
     * @brief Keeps time across the system
     *
     * Will be a singleton that will be used to keep time
     *
     * @todo needs more work
     */
    class TimeGeneration
    {
    public:
        //! Constructor
        TimeGeneration();
        //! Denstructor
        ~TimeGeneration();

        //! Returns the time that the program has been running for as a date/time string
        std::string getUpTimeStamp();
        //! Returns the time in milliseconds that the program has been running for
        long long getUpTimeMicS();
        //! Returns the time since EPOCH as a date/time string
        std::string getCurrentTimeStamp();
        //! Returns the microseconds since EPOCH
        long long getCurrentTimeMicS();

    private:
        //! tm struct we'll use
        const struct tm startDate;
    };
}

#endif /* PROTOCOLDEVELOPER_TIMEGENERATION_H */
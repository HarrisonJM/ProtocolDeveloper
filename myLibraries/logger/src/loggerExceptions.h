/*!
 * @brief Defines exceptions to be used by the logger
 *
 * @author hmarcks
 *
 * @date 10/04/19
 *
 * @addtogroup logger
 * @{
 * @addtogroup exceptions
 * @{
 */

#ifndef PROTOCOLDEVELOPER_LOGGEREXCEPTIONS_H
#define PROTOCOLDEVELOPER_LOGGEREXCEPTIONS_H

#include <exception>

namespace logger {

class loggerException : public std::exception
{
public:
    virtual const char *what()
    {
        return "Logfile has encountered an error";
    }
};

class log_mapOutOfBounds : public loggerException
{
public:
    const char *what() override
    {
        return "Requested log file out of bounds/doesn't exist";
    }
};

class log_logIDMinusOne : public loggerException
{
public:
    const char *what() override
    {
        return "Provided logID is -1. Did the file open?";
    }
};

} /* namespace logger */
/*! @} @} */
#endif //PROTOCOLDEVELOPER_LOGGEREXCEPTIONS_H

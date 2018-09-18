/*!
 * @brief Defines exceptions to be used by the logger
 */

#ifndef PROTOCOLDEVELOPER_LOGGEREXCEPTIONS_H
#define PROTOCOLDEVELOPER_LOGGEREXCEPTIONS_H

#include <exception>

namespace LoggerClasses {

class loggerException : public std::exception
{
public:
    virtual const char *what()
    {
        return "Logfile has encountered an error";
    }
};

class log_mapOutOfBounds : public std::exception
{
public:
    virtual const char *what()
    {
        return "Requested log file out of bounds/doesn't exist";
    }
};

class log_logIDMinusOne : public std::exception
{
public:
    virtual const char *what()
    {
        return "Provided logID is -1. Did the file open?";
    }
};

} /* namespace LoggerClasses */

#endif //PROTOCOLDEVELOPER_LOGGEREXCEPTIONS_H

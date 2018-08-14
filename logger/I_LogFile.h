/*!
 * @brief Interface for logger class
 *
 * @author hmarcks
 *
 * @date 05 Jul 2018
 *
 * @addtogroup LoggerClass
 */

#ifndef PROTOCOLDEVELOPER_I_LOGGER_H
#define PROTOCOLDEVELOPER_I_LOGGER_H

#include <string>

namespace LoggerClasses {

class I_LogFile
{
public:
    virtual ~I_LogFile();
    enum class logLevel : char
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };
    //! Adds a message to the log queue
    virtual void AddLogMessage(std::string message,
                               logLevel lvl) = 0;
    //! Writes all messages to file
    virtual void WriteAllMessagesToFile() = 0;
};

} /* namespace LoggerClass */

#endif //PROTOCOLDEVELOPER_I_LOGGER_H
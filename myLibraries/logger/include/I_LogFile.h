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

#include "logger/loggerUtility.h"

namespace LoggerClasses {

class I_LogFile
{
public:
    virtual ~I_LogFile() = default;
    //! Adds a message to the log queue
    virtual void AddLogMessage(std::string message,
                               logLevel lvl) = 0;
    //! Returns the oldest message in the queue
    virtual std::string ReturnOldestMessage() = 0;
    //! Writes The oldest message from the queue to the provided stream
    virtual void WriteAllMessagesToStream() = 0;
    //! Returns the latest message to be added
    virtual std::string ReturnLatestMessage() =0;
};

} /* namespace LoggerClass */

#endif //PROTOCOLDEVELOPER_I_LOGGER_H
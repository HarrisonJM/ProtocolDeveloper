/*!
 * @brief Defines interface for the log handler class
 *
 * @author hmarcks
 * @date 12/08/18
 * @addtogroup LoggerClasses
 */

#ifndef PROTOCOLDEVELOPER_I_LOGHANDLER_H
#define PROTOCOLDEVELOPER_I_LOGHANDLER_H

#include <string>
#include <cstdint>
#include "I_LogFile.h"
#include "logger/loggerUtility.h"

namespace LoggerClasses {

class I_LogHandler
{
public:
    //! Destructor
    virtual ~I_LogHandler() { };

    //! Opens a new log file, returns the ID of the newly opened log, no EIS
    virtual int64_t OpenNewLog(std::string logName,
                               StrategyEnums strategy) = 0;
    //! Opens a new log file, returns the ID of the newly opened log
    virtual int64_t OpenNewLog(std::string logName,
                               std::string EIS,
                               StrategyEnums strategy) = 0;
    //! Closes a log file, based on the logs ID
    virtual void CloseLog(int64_t logID) = 0;
    //! Closes a log file
    virtual void CloseLog(std::string logName) = 0;
    //! Closes all Log files
    virtual void CloseAllLogs() = 0;

    //! Adds a message to a log using the log ID
    virtual void AddMessageToLog(const int64_t logID,
                                 const std::string message,
                                 const logLevel lvl) const = 0;
    //! Adds a message to a log using the logs file name
    virtual void AddMessageToLog(const std::string logName,
                                 const std::string message,
                                 const logLevel lvl) const = 0;
    //! Returns an entire, specific, log based on its ID
    virtual I_LogFile *GetLogFileID(int64_t logID) const = 0;
    //! Returns an entire, specific, log based on its name
    virtual I_LogFile *GetLogFileName(std::string logName) const= 0;
    //! Flush messages to stream
    virtual void FlushMessagesToStreams() = 0;
    //! Sets the internal killHandler to false
    virtual void KillHandler() = 0;
};

} /* namespace LoggerClasses */

#endif //PROTOCOLDEVELOPER_I_LOGHANDLER_H

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
#include "I_LogFile.h"
#include "ThreadPool.h"

namespace LoggerClasses {
class I_LogHandler
{
public:
    //! Destructor
    virtual ~I_LogHandler() = 0;

    //! Opens a new log file, returns the ID of the newly opened log, no EIS
    virtual int64_t OpenNewLog(std::string logName) = 0;
    //! Opens a new log file, returns the ID of the newly opened log
    virtual int64_t OpenNewLog(std::string logName,
                               std::string EIS) = 0;
    //! Closes a log file, based on the logs ID
    virtual bool CloseLog(int64_t logID) = 0;
    //! Closes a log file
    virtual bool CloseLog(std::string logName) = 0;
    //! Closes all Log files
    virtual bool CloseAllLogs() = 0;

    //! Adds a message to a log using the log ID
    virtual bool AddMessageToLog(int64_t logID,
                                 std::string message,
                                 I_LogFile::logLevel lvl) = 0;
    //! Adds a message to a log using the logs file name
    virtual bool AddMessageToLog(std::string logName,
                                 std::string message,
                                 I_LogFile::logLevel lvl) = 0;
};

} /* namespace LoggerClasses */

#endif //PROTOCOLDEVELOPER_I_LOGHANDLER_H

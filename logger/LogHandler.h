/*!
 * @brief LogHandling class. Used for all/most Logs
 *
 * Will handle different logs and their respective threads
 *
 * @author hmarcks
 *
 * @date 12/08/18
 *
 * @addtogroup Logger
 */

#ifndef PROTOCOLDEVELOPER_LOGHANDLER_H
#define PROTOCOLDEVELOPER_LOGHANDLER_H

#include <string>
#include <map>

#include "I_LogHandler.h"
#include "LogFile.h"
#include "ThreadPool.h"

namespace LoggerClasses {
class LogHandler : public I_LogHandler
{
public:
    //! Constructor
    LogHandler(int maxLogs,
               std::string path,
               ThreadHandler::ThreadPool *threadHandler);
    //! Destructor
    ~LogHandler() override;

    //! Opens a new log file, returns the ID of the newly opened log, no EIS
    int64_t OpenNewLog(std::string logName) override;
    //! Opens a new log file, returns the ID of the newly opened log
    int64_t OpenNewLog(std::string logName,
                       std::string EIS) override;
    //! Closes a log file, based on the logs ID
    bool CloseLog(int64_t logID) override;
    //! Closes a log file
    bool CloseLog(std::string logName) override;
    //! Closes all Log files
    bool CloseAllLogs() override;

    //! Adds a message to a log using the log ID
    bool AddMessageToLog(int64_t logID,
                         std::string message,
                         I_LogFile::logLevel lvl) override;
    //! Adds a message to a log using the logs file name
    bool AddMessageToLog(std::string logName,
                         std::string message,
                         I_LogFile::logLevel lvl) override;

private:
    //! The thread pool used to handle log files
    ThreadHandler::ThreadPool *_logThreadPool;
    //! Maximum amount of threads to use for logging
    short _maxlogThreads;
    //! Will hold all open logs, referenced by an ID
    std::map<int64_t, LogFile *> _openLogs;
    //! Maps the log name to a specific ID
    std::map<std::string, int64_t> _nameToID;
    //! The maximum number of logs this handler can have open
    int _maxLogs;
    //! Holds the log prefix
    std::string _pathPrefix;
    //! Current log index
    u_int64_t _logIDIndex;

};
}

#endif //PROTOCOLDEVELOPER_LOGHANDLER_H

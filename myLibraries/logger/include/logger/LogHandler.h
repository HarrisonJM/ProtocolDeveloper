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
#include <condition_variable>

#include "I_LogHandler.h"
#include "I_LogFile.h"
#include "I_LogStrategy.h"
#include "threadPool/ThreadPool.h"

namespace LoggerClasses {

class LogHandler : public I_LogHandler
{
public:
    //! Constructor
    LogHandler(int maxLogs,
               std::string path);
    //! Constructor, testing
    LogHandler(int maxLogs,
               std::string path,
               I_LogStrategy* ilo);
    //! Destructor
    ~LogHandler() override;

    //! Opens a new log file, returns the ID of the newly opened log, no EIS
    int64_t OpenNewLog(std::string logName,
                       StrategyEnums strategy) override;
    //! Opens a new log file, returns the ID of the newly opened log
    int64_t OpenNewLog(std::string logName,
                       std::string EIS,
                       StrategyEnums strategy) override;
    //! Closes a log file, based on the logs ID
    void CloseLog(int64_t logID) override;
    //! Closes a log file
    void CloseLog(std::string logName) override;
    //! Closes all Log files
    void CloseAllLogs() override;

    //! Adds a message to a log using the log ID
    void AddMessageToLog(const int64_t logID,
                         const std::string message,
                         const logLevel lvl) const override;
    //! Adds a message to a log using the logs file name
    void AddMessageToLog(const std::string logName,
                         const std::string message,
                         const logLevel lvl) const override;
    //! Returns an entire, specific, log based on its ID
    I_LogFile* GetLogFileID(int64_t logID) const override;
    //! Returns an entire, specific, log based on its name
    I_LogFile* GetLogFileName(std::string logName) const override;
    //! Flush messages to stream
    void FlushMessagesToStreams() override;
    //! Sets the internal killHandler to false
    void KillHandler() override;

private:
    //! The strategy Handler
    I_LogStrategy* ilo_p;
    //! Will hold all open logs, referenced by an ID
    std::map<int64_t, I_LogFile *> _openLogs;
    //! Maps the log name to a specific ID
    std::map<std::string, int64_t> _nameToID;
    //! The maximum number of logs this handler can have open
    const int _maxLogs;
    //! The current Number of Open Logs
    int _numberOfOpenLogs;
    //! Holds the log prefix
    const std::string _pathPrefix;
    //! Current log index
    u_int64_t _logIDIndex;
    //! Conditional variable controlling message flushes
    std::condition_variable _condVar;
    //! Mutex to control conditional variable
    std::mutex _condMut;
    //! Kill handler
    bool _killHandler;
    //! Complete check
    bool _flushComplete;
};
}

#endif //PROTOCOLDEVELOPER_LOGHANDLER_H

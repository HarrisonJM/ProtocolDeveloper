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
#include <cstdint>

#include "I_LogHandler.h"
#include "I_LogFile.h"
#include "I_LogStrategy.h"
#include "threadPool/ThreadPool.h"

#define LOGMESSAGE(message_MACRO, level_MACRO) LoggerClasses::LogHandler::GetInstance(0, "").AddMessageToLog(_loggerID, message_MACRO, level_MACRO)

namespace LoggerClasses
{

class LogHandler
    : public I_LogHandler
{
private:
    //! Constructor
    LogHandler(int maxLogs
               , std::string path);
    //! Constructor, Mainly for testing
    LogHandler(int maxLogs
               , std::string path
               , std::shared_ptr<I_LogStrategy> ilo);
public:
    //! Destructor
    ~LogHandler() override;
    static LogHandler& GetInstance(int maxLogs
                                   , std::string path);
    static LogHandler& GetInstance(int maxLogs
                                   , std::string path
                                   , std::unique_ptr<I_LogStrategy> ilo);
    //! Opens a new log file, returns the ID of the newly opened log, no EIS
    int64_t OpenNewLog(const std::string& logName
                       , StrategyEnums strategy) override;
    //! Opens a new log file, returns the ID of the newly opened log
    int64_t OpenNewLog(const std::string& logName
                       , const std::string& EIS
                       , StrategyEnums strategy) override;
    //! Closes a log file, based on the logs ID
    void CloseLog(int64_t logID) override;
    //! Closes a log file
    void CloseLog(const std::string& logName) override;
    //! Closes all Log files
    void CloseAllLogs() override;

    //! Adds a message to a log using the log ID
    void AddMessageToLog(int64_t logID
                         , const std::string& message
                         , logLevel lvl) const override;
    //! Adds a message to a log using the logs file name
    void AddMessageToLog(const std::string& logName
                         , const std::string& message
                         , logLevel lvl) const override;
    //! Returns an entire, specific, log based on its ID
    std::shared_ptr<I_LogFile> GetLogFileByID(int64_t logID) const override;
    //! Returns an entire, specific, log based on its name
    std::shared_ptr<I_LogFile> GetLogFileByName(const std::string& logName) const override;
    //! Flush messages to stream
    void FlushMessagesToStreams() override;
    //! Sets the internal killHandler to false
    void KillHandler() override;

private:
    //! The strategy Handler
    const std::shared_ptr<I_LogStrategy> _ilo_p;
    //! Will hold all open logs, referenced by an ID
    std::map<int64_t, std::shared_ptr<I_LogFile>> _openLogs;
    //! Maps the log name to a specific ID
    std::map<std::string, int64_t> _nameToID;
    //! The maximum number of logs this handler can have open
    const int _maxLogs;
    //! The current Number of Open Logs
    int _numberOfOpenLogs;
    //! Holds the log prefix
    const std::string _pathPrefix;
    //! Current log index
    uint64_t _logIDIndex;
    //! Conditional variable controlling message flushes
    std::condition_variable _condVar;
    //! Mutex to control conditional variable
    std::mutex _condMut;
    //! Kill handler
    bool _killHandler;
    //! Complete check
    bool _flushComplete;
    /*!
     * @brief Creates the log handler instance (Meyers' Singleton)
     * @param maxLogs The maxmimum number of logs we can have open at once
     * @param path The Directory to store logs in (will be prepended to log file names
     * @param a uniqueptr containing the strategy implementation we want to use
     * @return A reference to the loghandler
     */
    static LogHandler& _GetInstance(int maxLogs
                                    , std::string path
                                    , std::shared_ptr<I_LogStrategy> ilo);
};

}

#endif //PROTOCOLDEVELOPER_LOGHANDLER_H

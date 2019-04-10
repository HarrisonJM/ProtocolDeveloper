/*!
 * @brief LogHandling class. Used for all/most Logs
 *
 * Will handle different logs and their respective threads
 *
 * @author hmarcks
 *
 * @date 12/08/18
 *
 * @addtogroup logger
 * @{
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
/*!
 * @brief Macro that requires whatever is using it to have a "_loggerID" variable in scope
 */
#define LOGMESSAGE(message_MACRO, level_MACRO) logger::LogHandler::GetInstance(0, "").AddMessageToLog(_loggerID, message_MACRO, level_MACRO)

namespace logger
{
/*!
 * @brief The log handler class. Handles The duties of creation and message comittal
 */
class LogHandler
    : public I_LogHandler
{
private:
    /*!
     * @brief Constructor
     * @param maxLogs Maximum number of logs
     * @param path The path to the logs
     */
    LogHandler(int maxLogs
               , std::string path);
    /*!
     * @brief Constructor, Mainly for testing
     * @param maxLogs Maximum number of logs
     * @param path The path to the logs
     * @param ilo An implementation of the log strategy
     */
    LogHandler(int maxLogs
               , std::string path
               , std::shared_ptr<I_LogStrategy> ilo);
public:
    //! Destructor
    ~LogHandler() override;
    /*!
     * @brief Returns the singleton instance
     * @param maxLogs The maximum number of logs we can have open
     * @param path The path to the log files
     * @return A reference to our singleton handler
     */
    static LogHandler& GetInstance(int maxLogs
                                   , std::string path);
    /*!
     * @brief Returns the singleton instance
     * @param maxLogs The maximum number of logs we can have open
     * @param path The path to the log files
     * @param ilo The log strategy we wish to use (for testing)
     * @return A reference to our singleton handler
     */
    static LogHandler& GetInstance(int maxLogs
                                   , std::string path
                                   , std::unique_ptr<I_LogStrategy> ilo);
    /*!
     * @brief Opens a new log file, returns the ID of the newly opened log, no EIS
     * @param logName The name of the log
     * @param strategy How/where the messages should be printed
     * @return The ID of the newly opened log file
     */
    int64_t OpenNewLog(const std::string& logName
                       , StrategyEnums strategy) override;
    /*!
     * @brief Opens a new log file, returns the ID of the newly opened log
     * @param logName The name of the log
     * @param EIS The "extra information" string that will be printed at the
     * top of a log file to denote more detail.
     * @param strategy How/where the messages should be printed
     * @return The ID of the newly opened log file
     */
    int64_t OpenNewLog(const std::string& logName
                       , const std::string& EIS
                       , StrategyEnums strategy) override;
    /*!
     * @brief Closes the log file referred to by logID
     * @param logID The log ID of the file we wish to close
     */
    void CloseLog(int64_t logID) override;
    /*!
     * @brief Closes the log file referred to by its name
     * @param logName The name of the log file we wish to close
     */
    void CloseLog(const std::string& logName) override;
    /*!
     * @brief Closes all open log files handled by this handler
     */
    void CloseAllLogs() override;
    /*!
     * @brief Adds a message to a log using the log ID
     * @param logID The log we wish to add a message to
     * @param message The message we wish to print
     * @param lvl The severity of the message
     */
    void AddMessageToLog(int64_t logID
                         , const std::string& message
                         , logLevel lvl) const override;
    /*!
     * @brief Adds a message to a log using the log's name
     * @param logName The log we wish to add a message to
     * @param message The message we wish to print
     * @param lvl The severity of the message
     */
    void AddMessageToLog(const std::string& logName
                         , const std::string& message
                         , logLevel lvl) const override;
    /*!
     * @brief Returns an entire, specific, log based on its ID
     * @param logID The id of the log we wish to retrieve
     * @return A shared_ptr to the log file we want
     */
    std::shared_ptr<I_LogFile> GetLogFileByID(int64_t logID) const override;
    /*!
     * @brief Returns an entire, specific, log based on its ID
     * @param logName The name of the log we wish to retrieve
     * @return A shared_ptr to the log file we want
     */
    std::shared_ptr<I_LogFile> GetLogFileByName(const std::string& logName) const override;
    /*!
     * @brief Flushes all log messages to their respective streams
     */
    void FlushMessagesToStreams() override;
    /*!
     * @brief Sets the killhandler to die
     */
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

} /* namespace logger */
/*! @} */
#endif //PROTOCOLDEVELOPER_LOGHANDLER_H

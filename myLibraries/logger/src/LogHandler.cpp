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

#include <functional>
#include <sstream>
#include <logger/LogHandler.h>

#include "logger/LogHandler.h"
#include "LogFile.h"
#include "LogHandlerStrategy.h"
#include "loggerExceptions.h"

namespace logger
{
/*!
 * @brief Constructor
 * @param maxLogs The maxmimum number of logs we can have open at once
 * @param path The Directory to store logs in (will be prepended to log file names
 */
LogHandler::LogHandler(int maxLogs
                       , std::string path)
    :
    _ilo_p(std::make_shared<LogHandlerStrategy>(LogHandlerStrategy()))
    , _openLogs()
    , _nameToID()
    , _maxLogs(maxLogs)
    , _numberOfOpenLogs(0)
    , _pathPrefix(std::move(path))
    , _logIDIndex(0)
    , _condVar()
    , _condMut()
    , _killHandler(false)
    , _flushComplete(false)
{
}
/*!
 * @brief Constructor
 * @param maxLogs The maxmimum number of logs we can have open at once
 * @param path The Directory to store logs in (will be prepended to log file names
 * @param ilo a uniqueptr containing the strategy implementation we want to use
 */
LogHandler::LogHandler(int maxLogs
                       , std::string path
                       , std::shared_ptr<I_LogStrategy> ilo)
    :
    _ilo_p(std::move(ilo))
    , _openLogs()
    , _nameToID()
    , _maxLogs(maxLogs)
    , _numberOfOpenLogs(0)
    , _pathPrefix(std::move(path))
    , _logIDIndex(0)
    , _condVar()
    , _condMut()
    , _killHandler(false)
    , _flushComplete(false)
{
}
/*!
 * @brief Destructor
 */
LogHandler::~LogHandler()
{
    _killHandler = true;
    while (!_flushComplete);

    CloseAllLogs();
}
/*!
 * @brief Creates the log handler instance (Meyers' Singleton)
 * @param maxLogs The maxmimum number of logs we can have open at once
 * @param path The Directory to store logs in (will be prepended to log file names
 * @return A reference to the loghandler
 */
LogHandler& LogHandler::GetInstance(int maxLogs
                                    , std::string path)
{
    static std::shared_ptr<LogHandlerStrategy> strat;
    return _GetInstance(maxLogs
                        , std::move(path)
                        , std::move(strat));
}
/*!
 * @brief Creates the log handler instance (Meyers' Singleton)
 * @param maxLogs The maxmimum number of logs we can have open at once
 * @param path The Directory to store logs in (will be prepended to log file names
 * @param a uniqueptr containing the strategy implementation we want to use
 * @return A reference to the loghandler
 */
LogHandler& LogHandler::GetInstance(int maxLogs
                                    , std::string path
                                    , std::unique_ptr<I_LogStrategy> ilo)
{
    return _GetInstance(maxLogs
                        , path
                        , std::move(ilo));
}
/*!
 * @brief Opens a new log without an Extra Information
 * @param logName The name of the new log
 * @return The ID of the newly created log
 */
int64_t LogHandler::OpenNewLog(const std::string& logName
                               , StrategyEnums strategy = StrategyEnums::STDOUT)
{
    return OpenNewLog(logName
                      , ""
                      , strategy);
}
/*!
 * @brief Opens a new log
 * @param logName The name of the log
 * @param EIS Extra information to be written to the log
 * @return The ID of the newly created log, -1 on error
 */
int64_t LogHandler::OpenNewLog(const std::string& logName
                               , const std::string& EIS
                               , StrategyEnums strategy = StrategyEnums::FSTREAM)
{
    if (_numberOfOpenLogs > _maxLogs)
        return -1;

    LogHandlerStrategy strategySelector;
    auto newOSTream_p = strategySelector.returnOstream(strategy
                                                       , (_pathPrefix + "/" + logName));

    auto newLog = std::make_shared<LogFile>(logName
                                            , EIS
                                            , std::move(newOSTream_p)
                                            , _condVar);
    _openLogs[_logIDIndex] = newLog;
    _nameToID[logName] = _logIDIndex;
    _logIDIndex++;

    _numberOfOpenLogs++;
    return (_logIDIndex - 1);
}
/*!
 * @brief Close a log based on its ID
 * @param logID The ID of the lgo to close
 * @return True
 */
void LogHandler::CloseLog(int64_t logID)
{
    // Search for ID/logname pair
    auto it = _nameToID.begin();
    for (; it != _nameToID.end(); ++it)
        if (it->second == logID)
            break;
    // Erase that entry
    _nameToID.erase(it);
}
/*!
 * @brief Close a log based on its name
 * @param logName The name of the lgo to close
 */
void LogHandler::CloseLog(const std::string& logName)
{
    CloseLog(_nameToID[logName]);
}
/*!
 * @brief Close all currently open logs
 */
void LogHandler::CloseAllLogs()
{
    for (auto logID : _nameToID)
        CloseLog(logID.second);
}
/*!
 * @brief Adds a message to a currently open lgo based on its ID
 * @param logID The ID of the log to add a message to
 * @param message The message
 * @param lvl The level of the log as an enum
 */
void LogHandler::AddMessageToLog(int64_t logID
                                 , const std::string& message
                                 , logLevel lvl) const
{
    try
    {
        GetLogFileByID(logID)->AddLogMessage(message
                                             , lvl);
    }
    catch (log_logIDMinusOne& e)
    {
    }
    catch (std::exception& e)
    {
        throw log_mapOutOfBounds();
    }
}
/*!
 * @brief Adds a log message to an open log based on its name
 * @param logName The name of the lgo to add a message to
 * @param message The message
 * @param lvl The level of the lgo as an enum
 */
void LogHandler::AddMessageToLog(const std::string& logName
                                 , const std::string& message
                                 , logLevel lvl) const
{
    try
    {
        GetLogFileByName(logName)->AddLogMessage(message
                                                 , lvl);
    }
    catch (loggerException& e)
    {
        std::cerr << "Logger exception: " << e.what() << std::endl;
    }
}
/*!
 * @brief Returns a pointer to an opened log based on its ID
 * @param logID The ID of the log to return
 * @return A pointer to a log or an empty reference
 */
std::shared_ptr<I_LogFile> LogHandler::GetLogFileByID(int64_t logID) const
{
    std::shared_ptr<I_LogFile> logFile_shr = nullptr;

    try
    {
        logFile_shr = _openLogs.at(logID);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return logFile_shr;
}
/*!
 * @brief Returns a pointer to an opened log based on its ID
 * @param logName
 * @return A pointer to a log or an empty reference
 */
std::shared_ptr<I_LogFile> LogHandler::GetLogFileByName(const std::string& logName) const
{
    std::shared_ptr<I_LogFile> logFile_shr = nullptr;

    try
    {
        logFile_shr = _openLogs.at(_nameToID.at(logName));
    }
    catch (std::exception& e)
    {
        //! @todo personalised exceptions
        std::cout << e.what() << std::endl;
    }

    return logFile_shr;
}
/*!
 * @brief Flushes all all messages for logs to their respective streams
 *
 * Uses a conditional variable to know when there are messages to write
 */
void LogHandler::FlushMessagesToStreams()
{
    while (!_killHandler)
    {
        std::unique_lock<std::mutex> locker(_condMut);
        _condVar.wait(locker);

        for (auto lf : _openLogs)
            lf.second->WriteAllMessagesToStream();
    }

    for (auto lf : _openLogs)
        lf.second->WriteAllMessagesToStream();

    _flushComplete = true;
}
/*!
 * @brief sets the _killHandler member to true, allowing the handler to perform any last cleanup
 */
void LogHandler::KillHandler()
{
    _killHandler = true;
}
/*!
 * @brief Returns the singleton instance
 * @param maxLogs The maximum number of logs we can have open
 * @param path The path to the log files
 * @param ilo The log strategy we wish to use (for testing)
 * @return A reference to our singleton handler
 */
LogHandler& LogHandler::_GetInstance(int maxLogs
                                     , std::string path
                                     , std::shared_ptr<I_LogStrategy> ilo)
{
    static LogHandler instance(maxLogs
                               , path
                               , std::move(ilo));
    return instance;
}

} /* namespace logger */
/*! @} */
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

#include <functional>
#include "LogHandler.h"

namespace LoggerClasses {

/*!
 * @brief Constructor
 * @param maxLogs The maxmimum number of logs we can have open at once
 * @param path The Directory to store logs in (will be prepended to log file names
 * @param threadHandler A pointer to a pre-setup threadpool
 */
LogHandler::LogHandler(int maxLogs,
                       std::string path,
                       ThreadHandler::ThreadPool *threadHandler)
    : _logThreadPool(threadHandler)
      , _openLogs()
      , _nameToID()
      , _maxLogs(maxLogs)
      , _pathPrefix(std::move(path))
      , _logIDIndex(0)
{
    _logThreadPool->InitPool();
}
 /*!
  * @brief Destructor
  */
LogHandler::~LogHandler()
{
    CloseAllLogs();
    _logThreadPool->shutdown();
}
/*!
 * @brief Opens a new log without an Extra Information
 * @param logName The name of the new log
 * @return The ID of the newly created log
 */
int64_t LogHandler::OpenNewLog(std::string logName)
{
    return OpenNewLog((_pathPrefix+"/"+logName),
                      "");
}
/*!
 * @brief Opens a new log, also passing extra log information
 * @param logName The name of the log
 * @param EIS Extra information to be written to the log
 * @return The ID of the newly created log
 */
int64_t LogHandler::OpenNewLog(std::string logName,
                               std::string EIS)
{
    LogFile *newLog = new LogFile(logName,
                                  EIS);
    _openLogs[_logIDIndex] = newLog;
    _nameToID[logName] = _logIDIndex;

    auto function = std::bind(&LogFile::WriteAllMessagesToFile,
                              _openLogs[_logIDIndex]);
    _logThreadPool->AddTaskToQueue(function);
    _logIDIndex++;
    return (_logIDIndex - 1);
}
/*!
 * @brief Close a lgo based on its ID
 * @param logID The ID of the lgo to close
 * @return True
 */
bool LogHandler::CloseLog(int64_t logID)
{
    // Search for ID/logname pair
    auto it = _nameToID.begin();
    for(; it != _nameToID.end(); ++it)
        if(it->second == logID)
            break;
    // Erase that entry
    _nameToID.erase(it);

    delete _openLogs[logID];

    return true;
}
/*!
 * @brief Close a log based on its name
 * @param logName The name of the lgo to close
 * @return True
 */
bool LogHandler::CloseLog(std::string logName)
{
    return CloseLog(_nameToID[logName]);
}
/*!
 * @brief Close all currently open logs
 * @return True
 */
bool LogHandler::CloseAllLogs()
{
    for(auto logID : _nameToID)
        CloseLog(logID.second);

    return true;
}
/*!
 * @brief Adds a message to a currently open lgo based on its ID
 * @param logID The ID of the log to add a message to
 * @param message The message
 * @param lvl The level of the log as an enum
 * @return True
 */
bool LogHandler::AddMessageToLog(int64_t logID,
                                 std::string message,
                                 I_LogFile::logLevel lvl)
{
    _openLogs[logID]->AddLogMessage(message,
                                    lvl);

    return true;
}
/*!
 * @brief Adds a log message to an open log based on its name
 * @param logName The name of the lgo to add a message to
 * @param message The message
 * @param lvl The level of the lgo as an enum
 * @return True
 */
bool LogHandler::AddMessageToLog(std::string logName,
                                 std::string message,
                                 I_LogFile::logLevel lvl)
{
    AddMessageToLog(_nameToID[logName],
                    message,
                    lvl);
    return true;
}

} /* namespace LoggerClasses */

/*!
 * @brief Defines interface for the log handler class
 *
 * @author hmarcks
 * @date 12/08/18
 * @addtogroup logger
 * @{
 * @addtogroup interfaces
 * @{
 */

#ifndef PROTOCOLDEVELOPER_I_LOGHANDLER_H
#define PROTOCOLDEVELOPER_I_LOGHANDLER_H

#include <string>
#include <cstdint>
#include "I_LogFile.h"
#include "logger/loggerUtility.h"

namespace logger
{

class I_LogHandler
{
public:
    //! Destructor
    virtual ~I_LogHandler() = default;
    /*!
     * @brief Opens a new log file, returns the ID of the newly opened log, no EIS
     * @param logName The name of the log
     * @param strategy How/where the messages should be printed
     * @return The ID of the newly opened log file
     */
    virtual int64_t OpenNewLog(const std::string& logName
                               , StrategyEnums strategy) = 0;
    /*!
     * @brief Opens a new log file, returns the ID of the newly opened log
     * @param logName The name of the log
     * @param EIS The "extra information" string that will be printed at the
     * top of a log file to denote more detail.
     * @param strategy How/where the messages should be printed
     * @return The ID of the newly opened log file
     */
    virtual int64_t OpenNewLog(const std::string& logName
                               , const std::string& EIS
                               , StrategyEnums strategy) = 0;
    /*!
     * @brief Closes the log file referred to by logID
     * @param logID The log ID of the file we wish to close
     */
    virtual void CloseLog(int64_t logID) = 0;
    /*!
     * @brief Closes the log file referred to by its name
     * @param logName The name of the log file we wish to close
     */
    virtual void CloseLog(const std::string& logName) = 0;
    /*!
     * @brief Closes all open log files handled by this handler
     */
    virtual void CloseAllLogs() = 0;
    /*!
     * @brief Adds a message to a log using the log ID
     * @param logID The log we wish to add a message to
     * @param message The message we wish to print
     * @param lvl The severity of the message
     */
    virtual void AddMessageToLog(int64_t logID
                                 , const std::string& message
                                 , logLevel lvl) const = 0;
    /*!
     * @brief Adds a message to a log using the log's name
     * @param logName The log we wish to add a message to
     * @param message The message we wish to print
     * @param lvl The severity of the message
     */
    virtual void AddMessageToLog(const std::string& logName
                                 , const std::string& message
                                 , logLevel lvl) const = 0;
    /*!
     * @brief Returns an entire, specific, log based on its ID
     * @param logID The id of the log we wish to retrieve
     * @return A shared_ptr to the log file we want
     */
    virtual std::shared_ptr<I_LogFile> GetLogFileByID(int64_t logID) const = 0;
    /*!
     * @brief Returns an entire, specific, log based on its ID
     * @param logName The name of the log we wish to retrieve
     * @return A shared_ptr to the log file we want
     */
    virtual std::shared_ptr<I_LogFile> GetLogFileByName(const std::string& logName) const = 0;
    /*!
     * @brief Flushes all log messages to their respective streams
     */
    virtual void FlushMessagesToStreams() = 0;
    /*!
     * @brief Sets the killhandler to die
     */
    virtual void KillHandler() = 0;
};

} /* namespace logger */
/*! @} @} */
#endif //PROTOCOLDEVELOPER_I_LOGHANDLER_H

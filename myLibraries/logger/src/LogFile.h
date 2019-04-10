/*!
 * @brief Represents a Single log file that can be written to
 *
 * @author hmarcks
 *
 * @date 13/08/18
 *
 * @addtogroup logger
 */

#ifndef PROTOCOLDEVELOPER_LOGGER_H
#define PROTOCOLDEVELOPER_LOGGER_H

#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <condition_variable>

#include "I_LogFile.h"

#include "safeQueues/SafeQueue.h"
#include "utility/enumHandler.h"

namespace logger
{
class LogFile
    : public I_LogFile
{
public:
    LogFile(const std::string& logName
            , const std::string& EIS
            , std::unique_ptr<std::ostream> outFile
            , std::condition_variable& CV);
    ~LogFile() override;
    /*!
     * @brief Adds a message to a log using the log ID
     * @param message The message we wish to print
     * @param lvl The severity of the message
     */
    void AddLogMessage(const std::string& message
                       , logLevel lvl) override;
    /*!
     * @brief Grabs the oldest message from the queue
     * @return A std::string of the message
     */
    std::string ReturnOldestMessage() override;
    /*!
     * @brief Writes The oldest message from the queue to the provided stream
     */
    void WriteAllMessagesToStream() override;
    /*!
     * @brief Returns the latest message to be added
     * @return Returns the most recent message in the queue
     */
    std::string ReturnLatestMessage() override;
private:
    //! The log File stream
    std::unique_ptr<std::ostream> _logOutStream;
    //! The name of the log
    const std::string _logName;
    //! This string will hold CSVs and be used to populate th elog file with extra information
    std::string _extraInformationString;
    //! Handles the log level enums
    utility::EnumHandler<logLevel, std::string> _logLevels;
    //! Log message buffer
    safeContainers::SafeQueue<std::string> _messagesToWrite;
    //! Triggers a flush when there are pending messages
    std::condition_variable &_condVar;
    /*!
     * @brief Generates a header for the log file
     */
    void _GenerateHeader();
    /*!
     * @brief Parses the EIS string (if it was provided)
     * @param EISref The extra info string we wish to put in the log file
     * @return The parsed information string for printing
     */
    std::string extractEIS(std::string &EISref);
    /*!
     * @brief Generates a log message (adds timestamp, level, etc)
     * @param message The message we wsih to print
     * @param lvl it's severity
     * @return The message we wish to print
     */
    std::string _GenerateLogMessage(const std::string& message
                                    , logLevel lvl);
};
} /* namespace logger */
/*! @} */
#endif //PROTOCOLDEVELOPER_LOGGER_H

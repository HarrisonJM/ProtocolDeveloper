/*!
 * @brief Represents a Single log file that can be written to
 *
 * @author hmarcks
 *
 * @date 13/08/18
 *
 * @addtogroup Logger
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
#include "enumHandler/enumHandler.h"

namespace LoggerClasses {
class LogFile : public I_LogFile
{
public:
    LogFile(std::string logName,
            std::string EIS,
            std::unique_ptr<std::ostream> outFile,
            std::condition_variable &CV);
    ~LogFile() override;
    //! Add a log message
    void AddLogMessage(std::string message,
                       logLevel lvl) override;
    //! Returns the oldest message to be written
    std::string ReturnOldestMessage() override;
    //! Writes The oldest message from the queue to the provided stream
    void WriteAllMessagesToStream() override;
    //! Returns the latest message to be written
    std::string ReturnLatestMessage() override;
private:
    //! The log File stream
    std::unique_ptr<std::ostream> _logOutStream;
    //! The name of the log
    const std::string _logName;
    //! This string will hold CSVs and be used to populate th elog file with extra information
    std::string _extraInformationString;
    //! Handles the log level enums
    Utility::EnumHandler<logLevel, std::string> _logLevels;
    //! Log message buffer
    Utility::SafeQueue<std::string> _messagesToWrite;
    //! Triggers a flush when there are pending messages
    std::condition_variable &_condVar;

    //! Generates a header for the log file
    void _GenerateHeader();
    //! Extracts data from the EIS String
    std::string extractEIS(std::string &EISref);
    //! Generates a log message (adds timestamp, level, etc)
    std::string _GenerateLogMessage(std::string message,
                                    logLevel lvl);
};

} /* namespace LoggerClass */

#endif //PROTOCOLDEVELOPER_LOGGER_H

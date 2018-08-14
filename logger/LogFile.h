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
#include <mutex>

#include "enumHandler/enumHandler.h"
#include "SafeQueues/SafeQueue.h"
#include "I_LogFile.h"

namespace LoggerClasses {
class LogFile : public I_LogFile
{
public:
    LogFile(std::string logName,
           std::string EIS);
    ~LogFile() override;
    //! Add a log message
    void AddLogMessage(std::string message,
                       logLevel lvl) override;
    //! Writes all the backed up messages to the file
    void WriteAllMessagesToFile() override;
private:
    //! Will close our file stream
    bool _CloseLog();
    //! Opens a log ready for writing
    bool _OpenLog();
    //! The log File stream
    std::fstream _logFile;
    //! The name of the log
    const std::string _logName;
    //! This string will hold CSVs and be used to populate th elog file with extra information
    std::string _extraInformationString;
    //! Handles the log level enums
    Utility::EnumHandler<logLevel, std::string> _logLevels;
    //! Log message buffer
    Utility::SafeQueue<std::string> _messagesToWrite;
    //! Thread control, true means to stop
    bool _killThread;
    //! is the thread dead?
    bool _threadDead;

    void setKillThread(bool set);
    bool getKillThread();

    //! Generates a header for the log file
    void _GenerateHeader();
    //! Extracts data from the EIS String
    std::string extractEIS();
    //! Generates a log message (adds timestamp, level, etc)
    std::string _GenerateLogMessage(std::string message,
                                    logLevel lvl);
};

} /* namespace LoggerClass */

#endif //PROTOCOLDEVELOPER_LOGGER_H

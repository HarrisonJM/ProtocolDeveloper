/*!
 * @brief Main logger class
 *
 * Handles logging to a file. Thread safe
 *
 * @date 08/07/18
 *
 * @addtogroup LoggerClasses
 */

#include <sstream>
#include <map>

#include "utilityFunctions/stringUtility.h"
#include "LogFile.h"

namespace LoggerClasses {
/*!
 * @brief constructor
 * @param logName The full name of the log file
 * @param EIS  The extra information string
 */
LogFile::LogFile(std::string logName,
               std::string EIS)
    : _logFile()
      , _logName(std::move(logName))
      , _extraInformationString(std::move(EIS))
      , _logLevels()
      , _killThread(false)
      , _threadDead(false)
{
    _logLevels.RegisterEnum(I_LogFile::logLevel::ERROR,
                            "ERROR");
    _logLevels.RegisterEnum(I_LogFile::logLevel::INFO,
                            "INFO");
    _logLevels.RegisterEnum(I_LogFile::logLevel::DEBUG,
                            "DEBUG");
    _logLevels.RegisterEnum(I_LogFile::logLevel::WARNING,
                            "WARNING");
    _OpenLog();
}
/*!
 * @brief destructor
 */
LogFile::~LogFile()
{
    _killThread = true;
    _CloseLog();

    // Wait until thread is killed
    while(!_threadDead);
}
/*!
 * @brief Closes the log file if it's still open
 * @return The fail bit and whether the log was successfully closed
 */
bool LogFile::_CloseLog()
{
    if(_logFile.is_open())
        _logFile.close();

    return _logFile.fail();
}
/*!
 * @brief Opens a log for writing to
 * @param name The name of the og we wish to open
 * @return True for success
 */
bool LogFile::_OpenLog()
{
    if(!_logFile.is_open())
    {
        _logFile.open(_logName,
                      std::fstream::out);
        _GenerateHeader();
    }

    return _logFile.fail();
}
/*!
 * @brief Adds a log message to the message queue
 * @param message The message
 * @param lvl The log level
 * @return Whether the message was successfully added to the queue
 */
void LogFile::AddLogMessage(std::string message,
                            I_LogFile::logLevel lvl)
{
    std::string fullMessage = _GenerateLogMessage(message,
                                                  lvl);
    _messagesToWrite.push(fullMessage);
}
/*!
 * @brief Generates a header for the log file
 */
void LogFile::_GenerateHeader()
{
    std::string header;
    header + addXLetter(60, '*') + '\n';
    header + "Log file:          " + _logName + '\n';
    header + "Date:              " + "DATE REPLACE" + '\n';
    header + "Extra Information: ";

    std::string EIS = extractEIS();
    while(!EIS.empty())
    {
        header + EIS + '\n';
        header + addXLetter(15,
                               ' ');
        EIS = extractEIS();
    }

    header + addXLetter(60,
                           '*') + '\n';
    header + addXLetter(26,
                           '*')
             + " LOG STARTS BELOW "
             + addXLetter(26,
                           '*')
             + '\n';
    header + addXLetter(60,
                           '*') + '\n';
    header + '\n';

    _messagesToWrite.push(header);
}
/*!
 * @brief generates a log message
 * @param message The message we want to add
 */
std::string LogFile::_GenerateLogMessage(std::string message,
                                I_LogFile::logLevel lvl)
{
    std::string fullMessage;
    fullMessage += "[";
    fullMessage += _logLevels.getValue(lvl);
    fullMessage += "]";
    fullMessage += "[";
    fullMessage += "Date";
    fullMessage += "]: ";
    fullMessage += message;

    return fullMessage;
}
/*!
 * @brief Flushes the queue to a file, to be used as a separate task
 */
void LogFile::WriteAllMessagesToFile()
{
    _threadDead = false;

    while(!_killThread)
        while(!_messagesToWrite.empty())
        {
            std::string message;
            _messagesToWrite.pop_front(message);
            _logFile << message;
        }

    _threadDead = true;
}
/*!
 * @brief Extracts the extra string information. Needs to be looped over
 * @return A std::string containing the EIS or an empty string if nothing is present
 */
std::string LogFile::extractEIS()
{
    static std::stringstream sscheck(_extraInformationString);
    std::string token;

    if(getline(sscheck,
               token,
               ','))
        return token;

    return "";
}

/*!
 * @brief Sets the internal _killThread member
 * @param set The new value to be used
 */
void LogFile::setKillThread(bool set)
{
    _killThread = set;
}
/*!
 * @brief Returns the new thread value
 * @return The value of the internal _killThread member
 */
bool LogFile::getKillThread()
{
    return _killThread;
}

} /* namespace LoggerClass */


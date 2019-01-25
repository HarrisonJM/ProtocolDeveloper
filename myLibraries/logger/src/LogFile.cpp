/*!
 * @brief Main logger class
 *
 * Handles logging to a file. Thread safe
 *
 * @date 08/07/18
 *
 * @addtogroup LoggerClasses
 */

#include <ostream>
#include <map>
#include <sstream>

#include "utility.h"
#include "LogFile.h"

namespace LoggerClasses
{
/*!
 * @brief constructor
 * @param logName The full name of the log file
 * @param EIS  The extra information string
 */
LogFile::LogFile(const std::string& logName
                 , const std::string& EIS
                 , std::unique_ptr<std::ostream> outFile
                 , std::condition_variable& CV)
    : _logOutStream(std::move(outFile))
      , _logName(std::move(logName))
      , _extraInformationString(std::move(EIS))
      , _logLevels()
      , _condVar(CV)
{
    _logLevels.RegisterEnum(logLevel::ERROR,
                            "ERROR");
    _logLevels.RegisterEnum(logLevel::INFO,
                            "INFO");
    _logLevels.RegisterEnum(logLevel::DEBUG,
                            "DEBUG");
    _logLevels.RegisterEnum(logLevel::WARNING,
                            "WARNING");

    _GenerateHeader();
}
/*!
 * @brief destructor
 */
LogFile::~LogFile()
{
    while (!_messagesToWrite.empty());
}
/*!
 * @brief Adds a log message to the message queue
 * @param message The message
 * @param lvl The log level
 * @return Whether the message was successfully added to the queue
 */
void LogFile::AddLogMessage(const std::string& message
                            , logLevel lvl)
{
    std::string fullMessage = (_GenerateLogMessage(message,
                                                   lvl));
    // Notify the handler that there are now pending messages
    _condVar.notify_all();
    _messagesToWrite.push(fullMessage);
}
/*!
 * @brief Returns earliest written message of the log file
 * @return A string containing the oldest message
 */
std::string LogFile::ReturnOldestMessage()
{
    return _messagesToWrite.front();
}
/*!
 * @brief Writes all messages to the stream
 * @todo Use Conditional variable to trigger a buffer empty
 */
void LogFile::WriteAllMessagesToStream()
{
    while (!_messagesToWrite.empty())
    {
        std::string message;
        _messagesToWrite.pop_front(message);
        *_logOutStream << message;
    }
}
/*!
 * @brief Returns the latest message yet to be written to the log file
 * @return A std::string containing the message
 */
std::string LogFile::ReturnLatestMessage()
{
    return _messagesToWrite.back();
}
/*!
 * @brief Generates a header for the log file
 */
void LogFile::_GenerateHeader()
{
    std::string header;
    header += (addXLetter(60,
                          '*') + '\n');
    header += ("Log file:          " + _logName + '\n');
    header += (std::string("Date:              ") + "DATE REPLACE" + '\n');
    header += ("Extra Information: ");

    std::string EIStemp = _extraInformationString;
    std::string EIS = extractEIS(EIStemp);
    while (!EIS.empty())
    {
        header += (EIS + '\n');
        header += (addXLetter(15,
                              ' '));
        EIS = (extractEIS(EIStemp));
    }

    header += '\n';
    header += (addXLetter(60,
                          '*') + '\n');
    header += (addXLetter(21,
                          '*') + " LOG STARTS BELOW " + addXLetter(21,
                                                                   '*') + '\n');
    header += (addXLetter(60,
                          '*') + '\n');
    header += ('\n');

    _messagesToWrite.push(header);
}
/*!
 * @brief generates a log message
 * @param message The message we want to add
 * @todo date/time class
 */
std::string LogFile::_GenerateLogMessage(const std::string& message
                                         , logLevel lvl)
{
    std::string fullMessage;
    fullMessage += "[";
    fullMessage += _logLevels.getValue(lvl);
    fullMessage += "]";
    fullMessage += "[";
    //! @todo dating/timing mechanisms
    fullMessage += "Date";
    fullMessage += "]: ";
    fullMessage += message;
    fullMessage += "\n";

    return fullMessage;
}

/*!
 * @brief Extracts the extra string information. Needs to be looped over
 * @return A std::string containing the EIS or an empty string if nothing is present
 */
std::string LogFile::extractEIS(std::string &EISref)
{
    std::stringstream sscheck(EISref);
    std::string token;
    std::string returnVal;

    if (getline(sscheck,
                token,
                ','))
        returnVal = token;

    EISref.erase(EISref.find(returnVal),
                 returnVal.size() + 1);

    return returnVal;
}
} /* namespace LoggerClass */


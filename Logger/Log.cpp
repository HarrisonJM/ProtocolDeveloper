/*!
 * @brief Log
 *
 * @ingroup Logger
 *
 * Definitions for the Log class
 *
 * @date March 2018
 */
#include "Log.h"
#include "LoggerUtility.h"
#include "TimeGeneration.h"

#include <iostream>
#include <sstream>

namespace Logging
{
    /*!
     * @brief default_constructor
     *
     * Sets up the log without a key name (defaults to just log.log)
     * and then generates the header
     */
    Log::Log()
    : key("log.log"),
      logPath("logs/"),
      numberOfEntries(0),
      logFile((logPath+key), std::ios::in | std::ios::out),
      queueNeedsEmptying(false)
    {
        GenerateAndPrintLogHeader();
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief constructor
     *
     * Sets up the log with a key, which is used as the file name,
     * and then generates the header
     *
     * @param[in] in_key the key that will be used to reference the log
     *
     */
    Log::Log(std::string in_key)
        : key(in_key),
          logPath("logs/"),
          numberOfEntries(0),
          logFile((logPath+key), std::ios::in | std::ios::out),
          queueNeedsEmptying(false)
    {
        GenerateAndPrintLogHeader();
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief constructor
     *
     * Sets up the log with a key AND a path,
     * and then generates the header
     *
     * @param[in] in_key the key that will be used to reference the log
     * @param[in] in_path The path to where the log will be stored
     */
    Log::Log(std::string in_key,
    std::string in_path)
        : key(in_key),
          logPath(in_path),
          numberOfEntries(0),
          logFile((logPath+key), std::ios::in | std::ios::out),
          queueNeedsEmptying(false)
    {
        GenerateAndPrintLogHeader();
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief destructor
     */
    Log::~Log()
    {
        logFile.close();
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief GenerateAndPrintLogHeader
     *
     * Generates the log header and fills it out with any required information
     */
    void Log::GenerateAndPrintLogHeader()
    {
        logFile << "********************************************************************************" << std::endl;
        logFile << "** Log Name: " << key << std::endl;
        logFile
            << "** Log type: Test/System/Plugin/Communications/etc (I put this here, it's different valid types of log file) "
            << std::endl;
        logFile << "** Date Started: " << Utility::GenerateCurrentDate() << std::endl;
        logFile << "** Date Finished: " << std::endl;
        logFile << "********************************************************************************" << std::endl;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief AddLog
     *
     * Generates a log entry and adds it to the logEntryQueue to be later written to file.
     *
     * @param[in] logSeverity The severity of what is being logged
     * @param[in] logMessage The actual message we want to log
     * @param[in] loggedBy The Module/test/Whatever that is logging the message
     */
    void Log::AddLog(LOGSEVERITY_T logSeverity,
                     std::string logMessage,
                     std::string loggedBy)
    {
        //! \TODO: Generate log message
        //TODO: Tag for log is a bit unwiedly. Is the date required everytime?
        std::string newEntry;
        if (ended == false)
        {
            newEntry = newEntry + Utility::GenerateTimeStamp();
            newEntry = newEntry + '[' + GetLogSeverity(logSeverity) + ']';
            newEntry = newEntry + '[' + loggedBy + ']';
            newEntry = newEntry + ": " + logMessage;
        }

        logEntryQueue.push(newEntry);
        if (logEntryQueue.size() > 20)
            queueNeedsEmptying = true;

        ++numberOfEntries;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief getLogKey
     *
     * @return The key/nme of this log
     */
    std::string Log::getLogKey()
    {
        return this->key;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief getNumberOfEntries
     * @return the number of entries in the log
     */
    unsigned int Log::getNumberOfEntries()
    {
        return numberOfEntries;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief FlushQueueToFile
     *
     * Flushes the entries in the queue to file
     */
    void Log::FlushQueueToFile()
    {
        // Flushes the queue to the file
        while (logEntryQueue.empty() == false)
        {
            WriteEntry(logEntryQueue.pop_front());
        }

        queueNeedsEmptying = false;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief WriteEntry
     *
     * Writes a single entry to file.
     *
     * @param[in] entry
     */
    void Log::WriteEntry(std::string entry)
    {
        logFile << entry << std::endl;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief EndLog
     *
     * Signs the log off as ended
     */
    void Log::EndLog()
    {
        //! \TODO:
        // When logs are finished being written to they should be ended with some sort of character or
        // Sequence. This will allow Logs to be extended and to not end up with erroneous/trash entries
        // That are related to a different run. See below, however, this should still be done so we can
        // see when a test ended/finished. Or the program closed or soemthing
        // Create folders/directories for each run will be the best method
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief CountNumberOfEntries
     *
     * Counts the number of entries in the log file (excluding the header)
     */
    void Log::CountNumberOfEntries()
    {
        unsigned int numberOfRealLines = 0;
        while (!logFile.eof())
        {
            std::string temp;
            std::getline(logFile, temp);

            numberOfRealLines++;
        }

        numberOfEntries = numberOfRealLines - numberOfLinesUsedInHeader;
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief CheckLogAlreadyOpened
     *
     * Returns whether the log file is open or not.
     *
     * @return true if open, otherwise false.
     */
    bool Log::CheckLogAlreadyOpened()
    {
        return logFile.is_open();
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief CheckLogAlreadyEnded
     *
     * Checks to see if the log has been ended
     *
     * @return true if ended, otherwise false
     */
    bool Log::CheckLogAlreadyEnded()
    {
        return false;
    }

}

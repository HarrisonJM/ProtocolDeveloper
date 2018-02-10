#include "Log.h"
#include "LoggerUtility.h"
#include "TimeGeneration.h"

#include <iostream>
#include <sstream>

namespace Logging
{
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

    Log::~Log()
    {
        logFile.close();
    }

    //-------------------------------------------------------------------------

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

    void Log::AddLog(LOGSEVERITY_T logSeverity,
                     std::string logMessage,
                     std::string testName)
    {
        //! \TODO: Generate log message
        //TODO: Tag for log is a bit unwiedly. Is the date required everytime?
        std::string newEntry;
        if (ended == false)
        {
            newEntry = newEntry + Utility::GenerateTimeStamp();
            newEntry = newEntry + '[' + GetLogSeverity(logSeverity) + ']';
            newEntry = newEntry + '[' + testName + ']';
            newEntry = newEntry + ": " + logMessage;
        }

        logEntryQueue.push(newEntry);
        if (logEntryQueue.size() > 20)
            queueNeedsEmptying = true;

        ++numberOfEntries;
    }

    //-------------------------------------------------------------------------

    std::string Log::getLogKey()
    {
        return this->key;
    }

    //-------------------------------------------------------------------------

    unsigned int Log::getNumberOfEntries()
    {
        return numberOfEntries;
    }

    //-------------------------------------------------------------------------

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

    void Log::WriteEntry(std::string entry)
    {
        logFile << entry << std::endl;
    }

    //-------------------------------------------------------------------------

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

    bool Log::CheckLogAlreadyOpened()
    {
        return logFile.is_open();
    }

    //-------------------------------------------------------------------------

    bool Log::CheckLogAlreadyEnded()
    {
        return false;
    }

}

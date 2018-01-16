#include "Log.h"
#include "timeGeneration.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

namespace Logging
{
    Log::Log(std::wstring in_key)
        : key(in_key),
          numberOfEntries(0)
    {
        logPath = in_key;


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
        logFile << "** Log type: Test/System/Plugin/Communications/etc (I put this here, it's different valid types of log file) " << std::endl;
        logFile << "** Date Started: " << Utility::GenerateCurrentDate() << std::endl;
        logFile << "** Date Finished: " << std::endl;
        logFile << "********************************************************************************" << std::endl;
    }

    //-------------------------------------------------------------------------

    void Log::AddLog(LOGSEVERITY_T logSeverity, 
                     std::wstring logMessage, 
                     std::wstring testName)
    {
        //TODO: Generate log message
        //TODO: Tag for log is a bit unweidly. Is the date required everytime?
        std::wstring newEntry;
        if (ended == false)
        {
            newEntry = newEntry + L'[' + Utility::GenerateCurrentTimeString() + L']';
            newEntry = newEntry + L'[' + Utility::GenerateCurrentDate() + L']';
            newEntry = newEntry + L'[' + GetLogSeverity(logSeverity) + L']';
            newEntry = newEntry + L'[' + testName + L']';
            newEntry = newEntry + L": " + logMessage;
        }

        logEntryQueue.push(newEntry);
        ++numberOfEntries;
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
    }

    //-------------------------------------------------------------------------

    std::wstring Log::GetLogSeverity(LOGSEVERITY_T logSev)
    {
        switch (logSev)
        {
            case INFO: return L"INFO";
            case TRIVIAL: return L"TRIVIAL";
            case ISSUE: return L"ISSUE";
            case MAJOR: return L"MAJOR";
            case CRITICAL: return L"CRITICAL";
            case DEBUG: return L"DEBUG";
            default: return L"UNKNOWN SEVERITY GIVEN";
        }
    }

    //-------------------------------------------------------------------------

    void Log::WriteEntry(std::wstring entry)
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

    void Log::CountNumberOfEntries(std::wfstream &fileToCount)
    {
        int numberOfRealLines = 0;
        while(!fileToCount.eof())
        {
            std::wstring temp;
            std::getline(fileToCount, temp);

            numberOfRealLines++;
        }

        numberOfEntries = numberOfRealLines - numberOfLinesUsedInHeader;
    }

}

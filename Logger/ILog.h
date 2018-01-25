#pragma once

#include "LoggerDefinitions.h"
#include <fstream>
#include <queue>
#include <string>

namespace Logging {

	class ILog
	{
	public:
		virtual ~ILog() {}
        // Generate a log message and commit to the queue
        virtual void AddLog(LOGSEVERITY_T logSeverity, 
                            std::wstring logMessage, 
                            std::wstring testName) = 0;
        // Returns the number of entries in the log
        virtual unsigned int getNumberOfEntries() = 0;
        // Writes the entire queue to file.
        virtual void FlushQueueToFile() = 0;

        virtual std::wstring getLogKey() = 0;

    private:
        // Methods
        // Generates a header to place at the top of the log file
        virtual void GenerateAndPrintLogHeader() = 0;
        // Will check if the log already exists. True if exists, false otherwise
        virtual bool CheckLogAlreadyOpened() = 0;
        // Will check if a log has been previously ended. True if ended, false otherwise
        virtual bool CheckLogAlreadyEnded() = 0;
        // Writes a single from the front of the queue to the file pointer to by logFile
        virtual void WriteEntry(std::wstring entry) = 0;
        // Will terminate a log and "end" it so. All future openings of the file will be in readonly mode
        virtual void EndLog() = 0;
        // Counts all the entries in the log file (excludes the header)
        virtual void CountNumberOfEntries(std::wfstream &fileToCount) = 0;
	};
}
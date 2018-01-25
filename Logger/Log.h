#pragma once

#include "ILog.h"
#include "SafeQueue.h"

namespace Logging
{
	class Log : public ILog
	{
	public:
        // Constructor 
		explicit Log(std::wstring key);
		~Log();

        // Generate a log message and commit to the queue
        void AddLog(LOGSEVERITY_T logSeverity,
                            std::wstring logMessage, 
                            std::wstring testType) override;
        // Returns the number of entries in the log
        unsigned int getNumberOfEntries() override;
        // Writes the entire queue to file. Loop wrapper for Logging:Log::WriteEntry()
        void FlushQueueToFile() override;

		std::wstring getLogKey() override;

	protected:
		// The key will also serve as the filename
		std::wstring key; // This will serve as the TESTID, filename, and main logger identifier
        // Currently unused
		std::wstring logPath;
        // Tracks the number of entries in a file
		unsigned int numberOfEntries;
        // The file itself
        std::wfstream logFile;
        // tracks whether the log has ended. Will allow us to open the log in readonly mode.
        bool ended; 
		// The thread safe queue that entries that have yet to be written will be stored
		Utility::SafeQueue<std::wstring> logEntryQueue;
        // Number of lines the header uses, used in CountNumberOfEntries()
        const int numberOfLinesUsedInHeader = 6;

        // Methods
        // Generates a header to place at the top of the log file
		void GenerateAndPrintLogHeader() override;
        // Will check if the log already exists. True if exists, false otherwise
        bool CheckLogAlreadyOpened() override;
        // Will check if a log has been previously ended. True if ended, false otherwise
        bool CheckLogAlreadyEnded() override;
        // Writes a single from the front of the queue to the file pointer to by logFile
        void WriteEntry(std::wstring entry) override;
        // Will terminate a log and "end" it so. All future openings of the file will be in readonly mode
        void EndLog() override;
        // Counts all the entries in the log file (excludes the header)
        void CountNumberOfEntries(std::wfstream &fileToCount) override;
	};
}

/*!
 * @brief The basic Log object
 *
 * @ingroup Logger
 *
 * This class declares a single log file and any infomration that's associated with it.
 * It can be called directly, however it should be perferred to use the loghandler in most situations.
 *
 * @date March 2018
 *
 */
#ifndef __LOG_H__
#define __LOG_H__

#include "ILog.h"
#include "SafeQueue/SafeQueue.h"

namespace Logging
{
    /*!
     * A single log. Controls the input of a single file. Handles message queues,
     * and is thread safe. So multiple threads can write to the same log file, if need be.
     */
	class Log : public ILog
	{
	public:
        friend class LogTests;
        // Constructor
		Log();
		Log(std::string in_key);
        Log(std::string in_key, std::string in_path);
		~Log();

        // Generate a log message and commit to the queue
        void AddLog(LOGSEVERITY_T logSeverity,
                            std::string logMessage,
                            std::string loggedBy) override;
        // Returns the number of entries in the log
        unsigned int getNumberOfEntries() override;
        // Writes the entire queue to file. Loop wrapper for Logging:Log::WriteEntry()
        void FlushQueueToFile() override;
        // Returns the name of the log/test
		std::string getLogKey() override;
        // Will terminate a log and "end" it so. All future openings of the file will be in readonly mode
        void EndLog();

	private:
        // Number of lines the header uses, used in CountNumberOfEntries()
        const int numberOfLinesUsedInHeader = 6;
		// The key will also serve as the filename
		const std::string key; // This will serve as the TESTID, filename, and main logger identifier
        // Currently unused
		std::string logPath;
        // Tracks the number of entries in a file
		unsigned int numberOfEntries;
        // The file itself
        std::fstream logFile;
        // tracks whether the log has ended. Will allow us to open the log in readonly mode.
        bool ended;
        // when the queue is getting full will trigger this flag to be picked up as a priority
        bool queueNeedsEmptying;
		// The thread safe queue that entries that have yet to be written will be stored
		Utility::SafeQueue<std::string> logEntryQueue;

        // Methods
        // Generates a header to place at the top of the log file
		void GenerateAndPrintLogHeader();
        // Will check if the log already exists. True if exists, false otherwise
        bool CheckLogAlreadyOpened();
        // Will check if a log has been previously ended. True if ended, false otherwise
        bool CheckLogAlreadyEnded();
        // Writes a single from the front of the queue to the file pointer to by logFile
        void WriteEntry(std::string entry);
        // Counts all the entries in the log file (excludes the header)
        void CountNumberOfEntries();
    };
}

#endif /* __LOG_H__ */
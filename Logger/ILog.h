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
                            std::string logMessage,
                            std::string testName) = 0;
        // Returns the number of entries in the log
        virtual unsigned int getNumberOfEntries() = 0;
        // Writes the entire queue to file.
        virtual void FlushQueueToFile() = 0;

        virtual std::string getLogKey() = 0;
	};
}
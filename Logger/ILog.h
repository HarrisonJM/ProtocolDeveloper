#pragma once

#include "LoggerDefinitions.h"
#include <fstream>
#include <queue>
#include <string>

namespace Logging {

	class ILog
	{
	public:
        // Generate a log message and commit to the queue
        virtual void AddLog(LOGSEVERITY_T logSeverity, 
                            std::wstring logMessage, 
                            std::wstring testName) = 0;
        // Returns the number of entries in the log
        virtual unsigned int getNumberOfEntries() = 0;
        // Writes the entire queue to file.
        virtual void FlushQueueToFile() = 0;
	};
}
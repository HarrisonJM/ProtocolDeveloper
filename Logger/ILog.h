/*!
 * @brief Log Interface
 *
 * Defines the interface that the log class derives from
 *
 * @ingroup Logger
 *
 * @date March 2018
 *
 */
#ifndef PROTOCOLDEVELOPER_ILOG_H
#define PROTOCOLDEVELOPER_ILOG_H

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

#endif /*PROTOCOLDEVELOPER_ILOG_H*/
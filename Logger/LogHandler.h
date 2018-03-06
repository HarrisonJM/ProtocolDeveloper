/*!
 * @brief LogHandler
 *
 * The main Log handler for all logs. Is designed to be run as its own thread,
 * and spawn variosu threads for different tasks
 *
 * @ingroup Logger
 *
 * @date March 2018
 *
 */

#ifndef PROTOCOLDEVELOPER_LOGHANDLER_H
#define PROTOCOLDEVELOPER_LOGHANDLER_H

#include <string>
#include <map>
#include <mutex>
#include "ILog.h"
#include "LoggerDefinitions.h"

namespace Logging
{
	class LogHandler
	{
	public:
        friend class LogHandlerTests;

		LogHandler();
        explicit LogHandler(const std::string logDirectory_in);
		~LogHandler();

        //! @todo This
        // Needs a setup/init method or a more complicated constructor
        // Either way there will need to be a lot of configuration options for this bad boy
        // (Might/should hide everything behind macros and ifdefs)

        // Opens a new log by the name of the provided key
        void OpenLog(std::string logKey);

        // Adds a log to the file pointed to by logKey. Spawns a new thread for doing so
		int AddLog(std::string logKey,
                   LOGSEVERITY_T logSeverity, 
                   std::string logMessage,
                   std::string loggedBy);

        // Runs in a separate thread and loops over all logs flushing all their contents to file
        void flushLogs();
        // Provides a thread safe way of reading the killHandler
        bool getSetKillHandler(bool getSet);
        // Cycle through the threads and end them
        void closeAllLogs();

	protected:
		// Members
        // Contains all open logs mapped by their key/log name
		std::map<std::string, ILog*> openLogs;
        // Will end the loop checking for log files to write
		bool killHandler;
        // Defines the top level directory for logs
		std::string logDirectory;
        // A mutex key
        static std::mutex mut;
	};

}

#endif /* __LOGHANDLER_H__ */

#pragma once

#include <string>
#include <map>
#include "ILog.h"
#include "LoggerDefinitions.h"

namespace Logging {

	class LogHandler
	{
	public:
		LogHandler();
		~LogHandler();

        //! \TODO: This
        // Needs a setup/init method or a more complicated constructor
        // Either way there will need to be a lot fo configuration options for this bad boy
        // (Might/should hide everything behind macros and ifdefs)

        // Opens a new log by the name of the provided key
        void OpenLog(std::wstring logKey);

        // Adds a log to the file pointed to by logKey. Spawns a new thread for doing so
		int AddLog(std::wstring logKey, 
                   LOGSEVERITY_T logSeverity, 
                   std::wstring logMessage, 
                   std::wstring testType);

        // Runs in a separate thread and loops over all logs flushing all their contents to file
        void flushLogs();

	private:
		// Members
        // Contains all open logs mapped by their key/log name
		std::map<std::wstring, ILog*> openLogs;
	};


}

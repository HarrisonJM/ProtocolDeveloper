#include "LogHandler.h"
#include "Log.h"

#include <thread>
#include <chrono>

namespace Logging {

	LogHandler::LogHandler()
	{
		//! \TODO: Perhaps scan any currently existing logs in some folder
		// any logs that aren't "ended" can be re-opened
		// For now can stay el blanco

        // Logs logger failures
        //Log *newLog = new Log("Logger.log");
	}

    //-------------------------------------------------------------------------

	LogHandler::~LogHandler()
	{
		//! \TODO: Should close all opened logs in the map
	}

    //-------------------------------------------------------------------------

	void LogHandler::OpenLog(std::wstring logKey)
	{
        // Create a new log object
        Log *newLog = new Log(logKey);
        openLogs[logKey] = newLog;
	}

    //-------------------------------------------------------------------------

	int LogHandler::AddLog(std::wstring logKey, 
                           LOGSEVERITY_T logSeverity, 
                           std::wstring logMessage, 
                           std::wstring testName)
	{
        // Spawn a thread that will spin until it can write to the queue
        // This might help later when deciding on dropping/blocking messages
        std::thread t(&Logging::ILog::AddLog,
                      std::ref(openLogs[logKey]), 
                      logSeverity, 
                      logMessage,
                      testName);
        t.detach();

		return 1;
	}

    //-------------------------------------------------------------------------

    void LogHandler::flushLogs()
    {
        // Will flush the queues of all stored logfiles to their respective folders
        while (1)
        {
            for (auto& aSingleLog : openLogs)
            {
                aSingleLog.second->FlushQueueToFile();
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

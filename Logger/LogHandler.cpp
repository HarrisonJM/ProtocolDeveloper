#include "LogHandler.h"
#include "Log.h"

#include <thread>

namespace Logging {

    std::mutex LogHandler::mut;

	LogHandler::LogHandler()
    : killHandler(false),
      logDirectory("log/")
	{
		//! \TODO: Perhaps scan any currently existing logs in some folder
		// any logs that aren't "ended" can be re-opened
		// For now can stay el blanco

        // Logs logger failures
        //Log *newLog = new Log("LogHandler.log");
	}

    //-------------------------------------------------------------------------

    LogHandler::LogHandler(const std::string logDirectory_in)
        : killHandler(false),
          logDirectory(logDirectory_in)
    {
        //! \TODO: Perhaps scan any currently existing logs in some folder
        // any logs that aren't "ended" can be re-opened
        // For now can stay el blanco

        // Logs logger failures
        //Log *newLog = new Log("LogHandler.log");
    }

    //-------------------------------------------------------------------------

	LogHandler::~LogHandler()
	{
        closeAllLogs();
	}

    //-------------------------------------------------------------------------

	void LogHandler::OpenLog(std::string logKey)
	{
        Log *newLog = new Log(logKey, logDirectory);

        openLogs[logKey] = newLog;
	}

    //-------------------------------------------------------------------------

	int LogHandler::AddLog(std::string logKey,
                           LOGSEVERITY_T logSeverity, 
                           std::string logMessage,
                           std::string testName)
	{

        // Spawn a thread that will spin until it can write to the queue
        // This might help later when deciding on dropping/blocking messages
        //! \TODO: Exception handling
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
        while (getSetKillHandler(true) == false)
        {
            for (auto& aSingleLog : openLogs)
            {
                aSingleLog.second->FlushQueueToFile();
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    //-------------------------------------------------------------------------

    bool LogHandler::getSetKillHandler(bool getSet)
    {
        // get the killHandler
        if(getSet == true)
        {
            std::unique_lock<std::mutex> lock(mut);
            return killHandler;
        }
        else // Kill the handler
        {
            std::unique_lock<std::mutex> lock(mut);
            killHandler = true;
        }

        return true;
    }

    //-------------------------------------------------------------------------

    void LogHandler::closeAllLogs()
    {
        for(const std::pair<std::string,ILog*> logToClose : openLogs)
        {
            std::string key = logToClose.first;
            delete logToClose.second;
            openLogs.erase(key);
        }
    }
}

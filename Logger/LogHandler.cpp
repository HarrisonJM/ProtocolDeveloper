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
#include "LogHandler.h"
#include "Log.h"

#include <thread>

namespace Logging {

    /// The threading Mutex
    std::mutex LogHandler::mut;

    /*!
     * @brief default_constructor
     *
     * Default handler constructor. Defaults to storing in the log/ directory
     */
	LogHandler::LogHandler()
    : killHandler(false),
      logDirectory("log/")
	{
		//! @TODO: Perhaps scan any currently existing logs in some folder
		// any logs that aren't "ended" can be re-opened
		// For now can stay el blanco

        // Logs logger failures
        //Log *newLog = new Log("LogHandler.log");
	}

    //-------------------------------------------------------------------------

    /*!
     * @brief constructor
     *
     * Takes a string that decides the location the logs will take
     *
     * @param logDirectory_in where to store the logs
     */
    LogHandler::LogHandler(const std::string logDirectory_in)
        : killHandler(false),
          logDirectory(logDirectory_in)
    {
        //! @TODO: Perhaps scan any currently existing logs in some folder
        // any logs that aren't "ended" can be re-opened
        // For now can stay el blanco

        // Logs logger failures
        //Log *newLog = new Log("LogHandler.log");
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief destructor
     */
	LogHandler::~LogHandler()
	{
        closeAllLogs();
	}

    //-------------------------------------------------------------------------

    /*!
     * @brief OpenLog
     * Opens a log in the directory by the name of logKey and then puts it
     * into the log map
     * @param logKey The name and identifier of the log
     */
	void LogHandler::OpenLog(std::string logKey)
	{
        Log *newLog = new Log(logKey, logDirectory);

        openLogs[logKey] = newLog;
	}

    //-------------------------------------------------------------------------

    /*!
     * @brief AddLog
     *
     * Wrapper method that spawns a new thread to write into the logs entryQueue Log
     *
     * @param logKey The log's identifier
     * @param logSeverity The severity of the message
     * @param logMessage The message we want to log
     * @param loggedBy The Modole that's supplying the message
     * @return
     */
	int LogHandler::AddLog(std::string logKey,
                           LOGSEVERITY_T logSeverity, 
                           std::string logMessage,
                           std::string loggedBy)
	{

        // Spawn a thread that will spin until it can write to the queue
        // This might help later when deciding on dropping/blocking messages
        //! @todo: Exception handling
        std::thread t(&Logging::ILog::AddLog,
                      std::ref(openLogs[logKey]), 
                      logSeverity, 
                      logMessage,
                      loggedBy);
        t.detach();

		return 1;
	}

    //-------------------------------------------------------------------------

    /*!
     * @brief flushLogs
     *
     * flushes the queues of all sotred logs to file
     */
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

    /*!
     * @brief getSetKillHandler
     *
     * It's purpose annoys me and I don't know if I need it
     *
     * @param getSet Sets and or gets the killhandler.
     * @return
     */
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

    /*!
     * @brief closeAllLogs
     *
     * Closes all stored Logs
     */
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

#include <iostream>
#include <testRunner/testRunner.h>
#include <pluginLoader/pluginLoader.h>
#include <testAnalyser2/testAnalyser2.h>
#include <logger/LogHandler.h>
#include <iomanip>

int main(int argc
         , char** argv)
{
    ThreadHandler::ThreadPool pool(10);
    pool.InitPool();
    LoggerClasses::LogHandler::GetInstance(20
                                           , "/var/log/protdev/");
    std::function<void(void)> flushFunc = std::bind(&LoggerClasses::LogHandler::FlushMessagesToStreams
                                                    , &(LoggerClasses::LogHandler::GetInstance(0
                                                                                               , "")));
    pool.AddTaskToQueue(flushFunc);

    auto t = std::time(nullptr);
    auto tm = std::localtime(&t);
    //std::cout << std::put_time(tm, "%d-%m-%Y %H-%M-%S") << std::endl;
    std::stringstream ss;
    ss << std::put_time(tm
                        , "TESTRUN_%d-%m-%Y_%H-%M-%S");
    auto _loggerID = LoggerClasses::LogHandler::GetInstance(0
                                                            , "").OpenNewLog(ss.str()
                                                                             , LoggerClasses::StrategyEnums::FSTREAM);
    // Load plugins
    PluginLoader::PluginLoader PL(_loggerID);
    PL.ScanForComms("/home/hmarcks/src/builds/protDev-debug/myLibraries/libnetworkCommunication/");
    PL.ScanForProtocols("/home/hmarcks/src/builds/protDev-debug/myLibraries/helloWorldProtocol/");

    std::string testFileName = "../../../../ProtocolDeveloper/myLibraries/testAnalyser2/sntp.xml";

    try
    {
        testAnalyser2::TestAnalyser2 TA2(testFileName
                                         , _loggerID);
        TestRunner::TestRunner tr(testFileName
                                  , PL.getCommsPlugins()
                                  , PL.getProtocolPlugins()
                                  , std::make_unique<decltype(TA2)>(TA2)
                                  , pool
                                  , 0);
        tr.BeginTesting();

    } catch (std::exception& e)
    {
        LOGMESSAGE(e.what()
                   , LoggerClasses::logLevel::ERROR);
        exit(1);
    }

    return 0;
}

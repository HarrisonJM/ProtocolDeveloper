/*!
 * @brief Entry point for the protocol developer program
 *
 * @author hmarcks
 * @date 10/04/19
 * @addtogroup ProtDev
 * @{
 */
#include <iostream>
#include <testRunner/testRunner.h>
#include <pluginLoader/pluginLoader.h>
#include <testAnalyser2/testAnalyser2.h>
#include <logger/LogHandler.h>
#include <iomanip>

int main(int argc
         , char **argv)
{
    threadPool::ThreadPool pool(10);
    pool.InitPool();
    logger::LogHandler::GetInstance(20
                                           , "/var/log/protdev/");
    std::function<void(void)> flushFunc = std::bind(&logger::LogHandler::FlushMessagesToStreams
                                                    , &(logger::LogHandler::GetInstance(0
                                                                                               , "")));
    pool.AddTaskToQueue(flushFunc);

    auto t = std::time(nullptr);
    auto tm = std::localtime(&t);
    //std::cout << std::put_time(tm, "%d-%m-%Y %H-%M-%S") << std::endl;
    std::stringstream ss;
    ss << std::put_time(tm
                        , "TESTRUN_%d-%m-%Y_%H-%M-%S");
    auto _loggerID = logger::LogHandler::GetInstance(0
                                                            , "").OpenNewLog(ss.str()
                                                                             , logger::StrategyEnums::FSTREAM);
    // Load plugins
    pluginLoader::PluginLoader PL(_loggerID);
//    PL.ScanForComms("/home/hmarcks/src/builds/protDev-debug/myLibraries/NetworkCommunication/");
//    PL.ScanForProtocols("/home/hmarcks/src/builds/protDev-debug/myLibraries/helloWorldProtocol/");
    PL.ScanForComms("../../myLibraries/NetworkCommunication/");
    PL.ScanForProtocols("../../myLibraries/helloWorldProtocol/lib");

    std::string testFileName = "../../../../ProtocolDeveloper/myLibraries/testAnalyser2/sntp.xml";
//    std::string testFileName = "../../../../ProtocolDeveloper/myLibraries/testAnalyser2/broken.xml";

    try
    {
        testAnalyser2::TestAnalyser2 TA2(testFileName
                                         , _loggerID);
        testRunner::TestRunner tr(testFileName
                                  , PL.getCommsPlugins()
                                  , PL.getProtocolPlugins()
                                  , std::make_unique<decltype(TA2)>(TA2)
                                  , pool
                                  , 0);
        tr.BeginTesting();
    } catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        LOGMESSAGE(e.what()
                   , logger::logLevel::ERROR);
        exit(1);
    }

    return 0;
}
/*! @} */
/*!
 * @brief used to manually verify the logger was working/creating files.
 * Is not a part of production
 */
#include <iostream>

#include "logger/LogHandler.h"
#include "../../../myLibraries/logger/src/LogHandlerStrategy.h"

int main(int argc,
         char **argv)
{
    LoggerClasses::LogHandlerStrategy ls;
    auto foo = ls.returnOstream(LoggerClasses::StrategyEnums::STDOUT
                                , ".");
    *foo << "exmaple";

    LoggerClasses::LogHandler::GetInstance(5
                                           , ".").KillHandler();

    //////////////////////////////////////////////

    int64_t id2 = LoggerClasses::LogHandler::GetInstance(0
                                                         , "").OpenNewLog("stdout"
                                                                          ,
                                LoggerClasses::StrategyEnums::STDOUT);
    if(-1 == id2)
        exit(1);

    LoggerClasses::LogHandler::GetInstance(0
                                           , "").AddMessageToLog(id2
                                                                 ,
                       "BBBBBB",
                       LoggerClasses::logLevel::INFO);

    LoggerClasses::LogHandler::GetInstance(0
                                           , "").FlushMessagesToStreams();

    //////////////////////////////////////////

    int64_t id = LoggerClasses::LogHandler::GetInstance(0
                                                        , "").OpenNewLog("testyBoye"
                                                                         ,
                               LoggerClasses::StrategyEnums::FSTREAM);

    if(-1 == id)
        exit(1);

    LoggerClasses::LogHandler::GetInstance(0
                                           , "").AddMessageToLog(id
                                                                 ,
                       "AAAAA",
                       LoggerClasses::logLevel::INFO);

    ////////////////////////////////////////////

    std::cout << "DONE!" << std::endl;

    return 0;
}


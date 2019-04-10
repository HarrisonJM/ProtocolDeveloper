/*!
 * @brief used to manually verify the logger was working/creating files.
 * Is not a part of production
 */
#include <iostream>

#include "logger/LogHandler.h"
#include "../../../myLibraries/logger/src/LogHandlerStrategy.h"

int main(int argc
         , char** argv)
{
    logger::LogHandlerStrategy ls;
    auto foo = ls.returnOstream(logger::StrategyEnums::STDOUT
                                , ".");
    *foo << "exmaple";

    logger::LogHandler::GetInstance(5
                                    , ".").KillHandler();

    //////////////////////////////////////////////

    int64_t id2 = logger::LogHandler::GetInstance(0
                                                  , "").OpenNewLog("stdout"
                                                                   , logger::StrategyEnums::STDOUT);
    if (-1 == id2)
        exit(1);

    logger::LogHandler::GetInstance(0
                                    , "").AddMessageToLog(id2
                                                          , "BBBBBB"
                                                          , logger::logLevel::INFO);

    logger::LogHandler::GetInstance(0
                                    , "").FlushMessagesToStreams();

    //////////////////////////////////////////

    int64_t id = logger::LogHandler::GetInstance(0
                                                 , "").OpenNewLog("testyBoye"
                                                                  , logger::StrategyEnums::FSTREAM);

    if (-1 == id)
        exit(1);

    logger::LogHandler::GetInstance(0
                                    , "").AddMessageToLog(id
                                                          , "AAAAA"
                                                          , logger::logLevel::INFO);

    ////////////////////////////////////////////

    std::cout << "DONE!" << std::endl;

    return 0;
}


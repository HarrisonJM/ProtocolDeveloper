/*!
 * @brief used to manually verify the logger was working/creating files.
 * Is not a part of production
 */
#include <iostream>

#include "logger/LogHandler.h"

int main(int argc,
         char **argv)
{
    LoggerClasses::LogHandler lh(5,
                                 ".");
    lh.KillHandler();

    //////////////////////////////////////////////

    int64_t id2 = lh.OpenNewLog("stdout",
                                LoggerClasses::StrategyEnums::STDOUT);
    if(-1 == id2)
        exit(1);

    lh.AddMessageToLog(id2,
                       "BBBBBB",
                       LoggerClasses::logLevel::INFO);

    lh.FlushMessagesToStreams();

    //////////////////////////////////////////

    int64_t id = lh.OpenNewLog("testyBoye",
                               LoggerClasses::StrategyEnums::FSTREAM);

    if(-1 == id)
        exit(1);

    lh.AddMessageToLog(id,
                       "AAAAA",
                       LoggerClasses::logLevel::INFO);

    ////////////////////////////////////////////

    std::cout << "DONE!" << std::endl;

    return 0;
}


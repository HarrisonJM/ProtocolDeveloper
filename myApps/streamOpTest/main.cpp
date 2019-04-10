/*!
 * @brief
 *
 * @author hmarcks
 * @date 10/04/19
 * @addtogroup
 * @{
 */

#include "../../myLibraries/logger/src/LogHandlerStrategy.h"

int main()
{
    //stdoutstream
    logger::LogHandlerStrategy lh;
    auto foo = lh.returnOstream(logger::StrategyEnums::STDOUT
                                , "");
    //overloadstream
    auto bar = lh.returnOstream(logger::StrategyEnums::STDERR
                                , "");

    *foo << "BAPPS";
    *bar << "BOOPS";
}

/*! @} */
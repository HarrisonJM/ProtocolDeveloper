/*!
 * @brief Pure interface for the logger strategy
 */

#ifndef PROTOCOLDEVELOPER_I_LOGSTRATEGY_H
#define PROTOCOLDEVELOPER_I_LOGSTRATEGY_H

#include <ostream>
#include <memory>
#include "logger/loggerUtility.h"

namespace LoggerClasses {
class I_LogStrategy
{
public:
    //! Switchcase, strategy selector
    virtual std::unique_ptr<std::ostream> returnOstream(StrategyEnums strat,
                                                        std::string fileName) const = 0;
};
} /* namespace LoggerClasses */
#endif //PROTOCOLDEVELOPER_I_LOGSTRATEGY_H

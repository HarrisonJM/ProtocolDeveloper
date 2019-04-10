/*!
 * @brief Pure interface for the logger strategy
 *
 * @author hmarcks
 *
 * @date 10/04/19
 * @addtogroup logger
 * @{
 * @addtogroup interfaces
 * @{
 */

#ifndef PROTOCOLDEVELOPER_I_LOGSTRATEGY_H
#define PROTOCOLDEVELOPER_I_LOGSTRATEGY_H

#include <ostream>
#include <memory>
#include "logger/loggerUtility.h"

namespace logger {
/*!
 * @brief Log output strategy
 */
class I_LogStrategy
{
public:
    /*!
     * @brief returns the desired std::ostream base based on a StrategyEnum
     * @param strat The strategy we wish to select
     * @param fileName The filename of the file we wish to open
     * @return A unique_ptr contining the stream we wish to use
     */
    virtual std::unique_ptr<std::ostream> returnOstream(StrategyEnums strat
                                                        , const std::string& fileName) const = 0;
};
} /* namespace logger */
/*! @} @} */
#endif //PROTOCOLDEVELOPER_I_LOGSTRATEGY_H

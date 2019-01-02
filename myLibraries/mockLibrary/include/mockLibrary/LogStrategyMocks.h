/*!
 * @brief Mock header for the logStrategyClass
 */

#ifndef PROTOCOLDEVELOPER_LOGSTRATEGYMOCKS_H
#define PROTOCOLDEVELOPER_LOGSTRATEGYMOCKS_H

#include <gmock/gmock.h>

#include "I_LogStrategy.h"

namespace LoggerClasses {
class LogStrategyMocks : public I_LogStrategy
{
public:
    MOCK_CONST_METHOD2(returnOstream,
                 std::unique_ptr<std::ostream>(StrategyEnums
                     strat, std::string
                     fileName));
};
} /* namespace LoggerClasses */
#endif //PROTOCOLDEVELOPER_LOGSTRATEGYMOCKS_H

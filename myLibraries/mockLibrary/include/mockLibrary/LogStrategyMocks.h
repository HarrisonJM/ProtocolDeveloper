/*!
 * @brief Mock header for the logStrategyClass
 * @addtogroup mockLibrary
 * @{
 */

#ifndef PROTOCOLDEVELOPER_LOGSTRATEGYMOCKS_H
#define PROTOCOLDEVELOPER_LOGSTRATEGYMOCKS_H

#include <gmock/gmock.h>

#include "I_LogStrategy.h"

namespace logger {
class LogStrategyMocks : public I_LogStrategy
{
public:
    MOCK_CONST_METHOD2(returnOstream,
                 std::unique_ptr<std::ostream>(StrategyEnums
                     strat, std::string
                     fileName));
};
} /* namespace logger */
/*! @} */
#endif //PROTOCOLDEVELOPER_LOGSTRATEGYMOCKS_H

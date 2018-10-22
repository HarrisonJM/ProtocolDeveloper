/*!
 * @brief Stores operations that a thread must take
 *
 * Will be read by the protocol that will help describe what action to take
 * should a certain condition be met
 *
 * @addtogroup testCaseHandler
 *
 * @date 10/07/18
 */


#ifndef PROTOCOLDEVELOPER_OPERATIONS_H
#define PROTOCOLDEVELOPER_OPERATIONS_H

#include <string>

#include "opVarBase.h"

namespace testCaseHandler
{

class operation : public OpVarBase
{
public:
    operation(std::string operationName,
        std::string dataToActOn,
        std::string _valueToReach);
    ~operation();
    std::string getOperationName();

private:
};

}

#endif /*PROTOCOLDEVELOPER_OPERATIONS_H*/

/*!
 * @brief Stores information pertaining to a Datapoints desired operations
 *
 * @addtogroup testCaseHandler
 *
 * @date 10/07/18
 */

#include "operation.h"

namespace testCaseHandler
{

operation::operation(std::string operationName,
                     std::string dataToActOn,
                     std::string valueToReach)
                     : OpVarBase(operationName, dataToActOn, valueToReach)
{

}
operation::~operation()
{

}
std::string operation::getOperationName()
{
    return _getSpecialization();
}

} /* CHANGEME */
/*!
 * @brief Interprets a datapoint
 *
 * The compiler will output many of this class. Each one will contain a
 * variable that it will act on. These will be stored in a final "Data emitter"
 * class that will be loaded by the protocol. The protocol will then make calls
 * to it to get data from it.
 *
 * @addtogroup testCaseParser
 *
 * @date 03/Jun/2018
 */

#include "variable.h"

namespace testCaseHandler
{
/*!
 * @brief Constructor, 3 arguments, completely fills the object
 * @param name The name of the variable that corresponds to the Datapoints variable
 * @param startingValue The starting value of the Variable
 * @param actionToTake The action to take with the variable
 */
variable::variable(std::string name,
                   std::string actionToTake,
                   std::string startingValue)
    : OpVarBase(std::move(name),
        std::move(actionToTake),
        std::move(startingValue))
{

}

/*!
 * @brief Destructor
 */
variable::~variable()
{

}

/*!
 * @brief Getter, _action
 * @return The action we wish to perform on the variable
 */
std::string variable::getAction()
{
    return _getSpecialization();
}


} /* namespace testCaseHandler */
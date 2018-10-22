/*!
 * @brief Stores a single variable to be acted upon
 *
 * The compiler will output many of this class. Each one will contain a
 * variable that it will act on. These will be stored in a final "Data emitter"
 * class that will be loaded by the protocol. The protocol will then make calls
 * to it to get data from it.
 *
 * @addtogroup testCaseHandler
 *
 * @date 04/Jul/2018
 *
 */

#ifndef PROTOCOLDEVELOPER_VARIABLE
#define PROTOCOLDEVELOPER_VARIABLE

#include <string>
#include <functional>
#include "opVarBase.h"

namespace testCaseHandler
{

class variable : public OpVarBase
{
public:
    variable(std::string name,
             std::string startingValue,
             std::string actionToTake);
    ~variable();

    std::string getAction();

private:

};

}
#endif /*PROTOCOLDEVELOPER_VARIABLE*/

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

variable::variable(std::string name,
                   std::string startingValue)
{

}

variable::variable(std::string name)
{

}

variable::~variable()
{

}

} /* CHANGEME */
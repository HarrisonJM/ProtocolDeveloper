/*!
 * @brief An interpreted Data Point
 *
 * Emits built data items to be sent out by tests. Threadsafe
 *
 * @addtogroup testCaseHandler
 *
 * @date 4/Jul/2018
 */


#ifndef PROTOCOLDEVELOPER_DATAPOINT_H
#define PROTOCOLDEVELOPER_DATAPOINT_H

#include <map>
#include <memory>

#include "variable.h"
#include "operation.h"

namespace testCaseHandler
{

class DataPoint
{
public:
    DataPoint();
    ~DataPoint();

    void RegisterVariable(std::unique_ptr<variable> newTI);
    void RegisterOperation(std::unique_ptr<operation> newTI);
    std::string GetPattern();

    void setPattern(std::string pattern_in);
private:
    bool _patternSet;
    //! @brief Defines how the data will be built
    //! i.e. [foo][bar][baz] where each [] is a different variable
    std::string _pattern;
    //! @brief Stores all of the interpreters mapped by their variable names
    std::map<std::string, std::unique_ptr<variable>> _variables;
    //! @breif Stores any operations that need to be taken on this dataPoint
    std::map<std::string, std::unique_ptr<operation>> _operations;
};

}


#endif /* PROTOCOLDEVELOPER_DATAPOINT_H */

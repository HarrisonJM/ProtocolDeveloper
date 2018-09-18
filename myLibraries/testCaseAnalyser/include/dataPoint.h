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

#include "variable.h"

namespace testCaseHandler
{

class DataPoint
{
public:
    DataPoint();
    ~DataPoint();

    void RegisterVariable(variable newTI);
    std::string GetNextDataItem(int position);
    std::string GetNextDataItem();
    void setPattern(std::string pattern_in);
private:
    //! @brief Defines how the data will be built
    //! i.e. [foo][bar][baz] where each [] is a different variable
    std::string _pattern;
    //! @brief Stores all of the interpreters mapped by their variable names
    std::map<std::string, variable> _variables;
    //! @breif Stores any operations that need to be taken on this dataPoint
    std::map<std::string, variable> _operations;

};

}


#endif /* PROTOCOLDEVELOPER_DATAPOINT_H */

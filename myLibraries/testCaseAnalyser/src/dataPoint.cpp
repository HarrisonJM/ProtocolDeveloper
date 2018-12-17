/*!
 * @brief An entire datapoint
 *
 * Will need to be threadsafe so that multiple threads can access data items
 * (and the next data items) without breaking.
 *
 * Organises the variables and outputs as a std::string
 *
 * @addtogroup testCaseHandler
 *
 * @date 04/Jul/2018
 */


#include "dataPoint.h"

namespace testCaseHandler
{
/*!
 * @brief Constructor
 */
DataPoint::DataPoint()
    : _patternSet(false)
{
}
/*!
 * @brief Destructor
 */
DataPoint::~DataPoint()
{
}
/*!
 * @brief Registers a new Variable for use in the dataPoint
 * @param newTI A shared_ptr containing the new variable
 */
void DataPoint::RegisterVariable(std::unique_ptr<variable> newTI)
{
    _variables[newTI->getName()] = std::move(newTI);
}
/*!
 * @brief Registers a new operation for use in the datapoint
 * @param newTI A shared_ptr containing the operation
 */
void DataPoint::RegisterOperation(std::unique_ptr<operation> newTI)
{
    _operations[newTI->getName()] = std::move(newTI);
}
/*!
 * @brief Returns the the pattern
 * @return A string containing the pattern
 */
std::string DataPoint::GetPattern()
{
    return _pattern;
}
/*!
 * @brief Sets the datapoints pattern that we'll be editing
 * @param pattern_in The pattern we want to set for this dataPoint
 */
void DataPoint::setPattern(std::string pattern_in)
{
    if (!_patternSet)
        _pattern = pattern_in;
}
} /* CHANGEME */
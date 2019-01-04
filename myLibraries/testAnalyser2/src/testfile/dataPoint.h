/*!
 * @brief Represents a single data point
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#ifndef PROTOCOLDEVELOPER_DATAPOINT_H
#define PROTOCOLDEVELOPER_DATAPOINT_H

#include <string>
#include <vector>

namespace testAnalyser2
{
/*!
 * @brief A variable that will be changed
 * @{
 */
struct testVariable
{
    std::string _name; /*! < The name of the variable */
    std::string _action; /*! < The action it shoudl take*/
    std::string _value; /*! < The starting value */
};
/*!@}*/
/*!
 * @brief An operation on a variable
 */
struct testOperation
{
    std::string _name; /*! < The name of the operation */
    std::string _storedIn; /*! < What variable does this oepration act on*/
    std::string _value; /*! < The value that enables the operation */
};
/*!@}*/
/*!
 * @brief The datapoint itself, with related information
 */
struct dataPoint
{
    std::string _dataPoint; /*! < The data point itself i.e. [LI][VN][Mode][Stratum] */
    std::vector<testVariable> _variables; /*! < The variables present in the datapoint */
    std::vector<testOperation> _operations; /*! < The operations to take on this datapoint */
};
/*!@}*/
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_DATAPOINT_H */

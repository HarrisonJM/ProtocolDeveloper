/*!
 * @brief Stores at least one dataPoint and emits the dataPoints data
 *
 * @addtogroup testCaseHandler
 *
 * @date 10/07/18
 */

#include <dataEmitter.h>

#include "dataEmitter.h"

namespace testCaseHandler
{
/*!
 * @brief Constructor
 */
DataEmitter::DataEmitter()
: _numberOfDataPoints(0)
{

}
/*!
 * @brief Destructor
 */
DataEmitter::~DataEmitter()
{

}
/*!
 * @brief Registers a new dataPoint
 * @param newDataPoint A shared_ptr to the new datapoint
 */
void DataEmitter::RegisterDataPoint(std::shared_ptr<DataPoint> newDataPoint)
{
    _dataPoints[_numberOfDataPoints] = newDataPoint;
    ++_numberOfDataPoints;
}
/*!
 * @brief Accesses a datapoint referenced by position
 * @param position What dataPoint to access
 * @return A shared_ptr containing the dataPoint
 */
std::shared_ptr<DataPoint> DataEmitter::AccessDataPoint(int position)
{
    return _dataPoints.at(position);
}
/*!
 * @brief Getter, _numberofDataPoints
 * @return The number of registered data points
 */
int DataEmitter::getNumberOfDataPoints()
{
    return _numberOfDataPoints;
}

} /* CHANGEME */
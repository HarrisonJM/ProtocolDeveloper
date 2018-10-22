/*!
 * @brief Holds all the dataPoints
 *
 * @addtogroup testCaseHandler
 *
 * @date 10/07/18
 */


#ifndef PROTOCOLDEVELOPER_DATAEMITTER_H
#define PROTOCOLDEVELOPER_DATAEMITTER_H

#include <memory>

#include "dataPoint.h"

namespace testCaseHandler
{

class DataEmitter
{
public:
    DataEmitter();
    ~DataEmitter();

    void RegisterDataPoint(std::shared_ptr<DataPoint> newDataPoint);

    std::shared_ptr<DataPoint> AccessDataPoint(int position);
    int getNumberOfDataPoints();

private:
    int _numberOfDataPoints;
    std::map<int, std::shared_ptr<DataPoint>> _dataPoints;
};

}

#endif /*PROTOCOLDEVELOPER_DATAEMITTER_H*/

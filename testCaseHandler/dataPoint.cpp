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

DataPoint::DataPoint()
{

}

DataPoint::~DataPoint()
{

}

void DataPoint::RegisterVariable(variable newTI)
{

}

std::string DataPoint::GetNextDataItem()
{
    return "Hello";
}

std::string DataPoint::GetNextDataItem(int position)
{
    return "World";
}

} /* CHANGEME */
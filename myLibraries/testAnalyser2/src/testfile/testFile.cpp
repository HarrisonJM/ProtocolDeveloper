/*!
 * @brief Represents the testfile itself and is passed/used by the test handler
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#include <testAnalyser2/testFile.h>

namespace testAnalyser2
{

size_t TestFile::getNumberOfDataPoints()
{
    return _dataPoints.size();
}
dataPoint& TestFile::GetDataPoint(int index)
{
    return _dataPoints[index];
}
std::vector<dataPoint>& TestFile::GetAllDataPoints()
{
    return _dataPoints;
}
void TestFile::AddDataPoint(dataPoint& newDP)
{
    _dataPoints.push_back(newDP);
}
void TestFile::AddConfiguration(testConfiguration& newConf)
{
    _configuration = std::move(newConf);
}
} /* namespace testAnalyser2 */
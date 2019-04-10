/*!
 * @brief Represents the testfile itself and is passed/used by the test handler
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 * @{
 * @date 02/01/19
 */

#include <testAnalyser2/testFile.h>

namespace testAnalyser2
{
/*!
 * @brief Returns the amount of data points present
 * @return a size_t with the number of datapoints stored
 */
size_t TestFile::GetNumberOfDataPoints()
{
    return _dataPoints.size();
}
/*!
 * @brief Returns a datapoint ref by the index it's stored at
 * @param index Which datapoint we want
 * @return A datapoint reference
 */
dataPoint& TestFile::GetDataPoint(int index)
{
    return _dataPoints[index];
}
/*!
 * @brief Returns a reference to the entire datapoint object vector
 * @return A reference to the entire datapoint object vector
 */
std::vector<dataPoint>& TestFile::GetAllDataPoints()
{
    return _dataPoints;
}
/*!
 * @brief Returns a const ref to the testconfiguration data
 * @return A const ref to the testconfiguration data
 */
const testConfiguration& TestFile::GetTestConfiguration()
{
    return _configuration;
}
/*!
 * @brief Adds a new datapoint to the internal vector
 * @param newDP A reference to the new datapoint
 */
void TestFile::AddDataPoint(dataPoint& newDP)
{
    _dataPoints.push_back(newDP);
}
/*!
 * @brief Adds a new testconfiguration to testfile representation
 * @param newConf A reference to the configuration
 */
void TestFile::AddConfiguration(testConfiguration& newConf)
{
    _configuration = std::move(newConf);
}
} /* namespace testAnalyser2 */
/*! @} */
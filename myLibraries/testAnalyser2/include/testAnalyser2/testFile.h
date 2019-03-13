/*!
 * @brief Represents the testfile itself and is passed/used by the test handler
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#ifndef PROTOCOLDEVELOPER_TESTFILE_H
#define PROTOCOLDEVELOPER_TESTFILE_H

#include <memory>
#include <vector>
#include <testAnalyser2/testfile/dataPoint.h>
#include <testAnalyser2/testfile/testConfiguration.h>

namespace testAnalyser2
{
/*!
 * @brief Object representation of a testfile
 */
class TestFile
{
public:
    TestFile() = default;
    ~TestFile() = default;
    /*!
     * @brief Returns the total number of datapoints
     * @return The number of datapoints as a size_t
     */
    size_t GetNumberOfDataPoints();
    /*!
     * @brief Gets a specific datapoint
     * @param index Which datapoint to get
     * @return A reference to that datapoint
     */
    dataPoint& GetDataPoint(int index);
    /*!
     * @brief Returns a reference to the vector containing all datapoints
     * @return A reference to the vector containing all data points
     */
    std::vector<dataPoint>& GetAllDataPoints();
    /*!
     * @brief Returns A const reference to the tests configuration information
     * @return A const ref to the object's Configuration data
     */
    const testConfiguration& GetTestConfiguration();
    /*!
     * @brief Adds a new datapoint to the testcase
     * @param newDP The new datapoint we wish to add
     */
    void AddDataPoint(dataPoint& newDP);
    /*!
     * @brief Adds the configuration to the testcase
     * @param newConf The configuration we wish to add
     */
    void AddConfiguration(testConfiguration& newConf);
private:
    /*!
     * @brief A vector containing all datapoints
     */
    std::vector<dataPoint> _dataPoints;
    /*!
     * @brief The test configuration itself
     */
    testConfiguration _configuration;
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_TESTFILE_H */

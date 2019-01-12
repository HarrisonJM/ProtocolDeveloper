/*!
 * @brief Kicks off the analysis. Interacts with the user
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#include <testAnalyser2/testAnalyser2.h>
#include "testObjectBuilder.h"
#include "analysisException.h"

namespace testAnalyser2
{
/*!
 * @brief Constructor
 * @param testfile The absolute location of the testfile
 */
TestAnalyser2::TestAnalyser2(std::string& testfile)
    : _testFileLoc(testfile)
{
}
/*!
 * @brief Begins the analysis of the testcase
 */
void TestAnalyser2::startAnalysis()
{
    TestObjectBuilder objBuil(_testFile
                              , _testFileLoc);
    try
    {
        objBuil.TopLevelNode();
        _analysed = true;
    }
    catch (baseAnalyser_Exception const& e)
    {
        // Log error?
    }
}
/*!
 * @brief Returns the testfile (as long as it's completed)
 * @return A reference to an analysed testfile. If not completed, testfile will be empty
 */
TestFile& TestAnalyser2::GetTestFile()
{
    if (_analysed)
        return _testFile;

    auto blankboy = new TestFile;
    return *blankboy;
}
/*!
 * @brief Returns the analysed boolean, indicating whether or not the testfile has been analysed
 * @return true if analysed, otherwise false
 */
bool TestAnalyser2::isAnalysed()
{
    return _analysed;
}
} /* namespace testAnalyser2 */
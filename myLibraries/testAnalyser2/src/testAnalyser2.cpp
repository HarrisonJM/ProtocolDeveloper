/*!
 * @brief Kicks off the analysis. Interacts with the user
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#include <filesystem>

#include <testAnalyser2/testAnalyser2.h>
#include <logger/LogHandler.h>
#include "testObjectBuilder.h"
#include "analysisException.h"

namespace testAnalyser2
{
/*!
 * @brief Constructor
 * @param testfile The absolute location of the testfile
 * @exception analyserFileDoesntExist_Exception The requested testfile doesn't exist
 */
TestAnalyser2::TestAnalyser2(std::string& testfile
                             , const int64_t loggerID)
    : _loggerID(loggerID)
      , _testFileLoc(testfile)
{
    if (!std::filesystem::exists(_testFileLoc))
    {
        throw analyserFileDoesntExist_Exception(_testFileLoc.c_str());
    }
}
/*!
 * @brief Begins the analysis of the testcase
 */
void TestAnalyser2::startAnalysis()
{
    if(!isAnalysed())
    {
        TestObjectBuilder objBuil(_testFile
                                  , _testFileLoc);
        LOGMESSAGE("Analysis of testcase started"
                   , LoggerClasses::logLevel::INFO);
        try
        {
            objBuil.TopLevelNode();
            _analysed = true;
        }
        catch (parserExceptionBase& e)
        {
            LOGMESSAGE(e.what()
                       , LoggerClasses::logLevel::ERROR);
        }
        LOGMESSAGE("Analysis of testcase completed"
                   , LoggerClasses::logLevel::INFO);
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

    LOGMESSAGE("testcase not yet parsed"
               , LoggerClasses::logLevel::DEBUG);

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
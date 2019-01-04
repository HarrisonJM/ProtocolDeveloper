/*!
 * @brief Reads the testfile and stores it in configuration objects for
 * configuration and reading
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#ifndef PROTOCOLDEVELOPER_TESTFILEANALYSER_H
#define PROTOCOLDEVELOPER_TESTFILEANALYSER_H

#include <string>
#include <testAnalyser2/testFile.h>

namespace testAnalyser2
{

class TestAnalyser2
{
public:
    /*!
     * @brief Constructor
     * @param testfile The absolute location of the testfile
     */
    explicit TestAnalyser2(std::string& testfile);
    /*!
     * @brief destructor
     */
    ~TestAnalyser2() = default;
    /*!
     * @brief Starts the testfile analysis
     */
    void startAnalysis();
    /*!
     * @brief Returns a reference to the testfile object (That's ready for use)
     * @return A Testfile reference
     */
    TestFile& GetTestFile();
    /*!
     * @brief Returns whether or not the testfile has been analysed yet
     * @return true for analysed, otherwise false
     */
    bool isAnalysed();
private:
    /*!
     * @brief Whether the analysis has been performed/completed
     */
    bool _analysed;
    /*!
     * @brief The absolute location of the testfile that were want to analyse
     */
    const std::string _testFileLoc;
    /*!
     * @brief The testfile object itself
     */
    TestFile _testFile;
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_TESTFILEANALYSER_H */

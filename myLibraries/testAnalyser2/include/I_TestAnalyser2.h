/*!
 * @brief  Interface for the testAnalyser2 class
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 12/01/19
 */
#ifndef PROTOCOLDEVELOPER_I_TESTANALYSER2_H
#define PROTOCOLDEVELOPER_I_TESTANALYSER2_H

#include <testAnalyser2/testFile.h>

namespace testAnalyser2
{
class I_TestAnalyser2
{
public:
    /*!
     * @brief destructor
     */
    ~I_TestAnalyser2() = default;
    /*!
     * @brief Starts the testfile analysis
     */
    virtual void startAnalysis() = 0;
    /*!
     * @brief Returns a reference to the testfile object (That's ready for use)
     * @return A Testfile reference
     */
    virtual TestFile& GetTestFile() = 0;
    /*!
     * @brief Returns whether or not the testfile has been analysed yet
     * @return true for analysed, otherwise false
     */
    virtual bool isAnalysed() = 0;
};
} /* namespace TestAnalyser2 */

#endif /* PROTOCOLDEVELOPER_I_TESTANALYSER2_H */

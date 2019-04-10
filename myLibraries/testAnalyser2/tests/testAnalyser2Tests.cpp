/*!
 * @brief unit tests for the testAnalyser2. Runs ALL unit tests for the library
 *
 * @author hmarcks
 *
 * @addtogroup testCaseAnalyser2
 * @{
 * @addtogroup tests
 * @{
 *
 * @date 02/01/19
 */

#include <gtest/gtest.h>

int main(int argc
         , char** argv)
{
    ::testing::InitGoogleTest(&argc
                              , argv);
    return RUN_ALL_TESTS();
}


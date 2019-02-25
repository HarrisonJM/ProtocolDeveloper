/*!
 * @brief Defines the entry point for all tests within the Utility library
 *
 * @author hmarcks
 *
 * @date 22/02/19
 *
 * @addtogroup utility
 */

#include <gtest/gtest.h>

int main(int argc
         , char** argv)
{
    ::testing::InitGoogleTest(&argc
                              , argv);
    return RUN_ALL_TESTS();
}

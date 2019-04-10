/*!
 * @brief Defines entry point for a test (Is actually used for nearly all test suites.
 * I just can't figure out a nice tidy way of keeping it seperate)
 *
 * @author hmarcks
 *
 * @addtogroup logger
 * @{
 * @addtogroup tests
 * @{
 * @date 12/01/19
 */

#include <gtest/gtest.h>

int main(int argc
         , char** argv)
{
    ::testing::InitGoogleTest(&argc
                              , argv);
    return RUN_ALL_TESTS();
}

/*! @} @} */
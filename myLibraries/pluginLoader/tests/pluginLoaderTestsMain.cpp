/*!
 * @brief main function for the plguin loader tests
 *
 * @author hmarcks
 *
 * @addtogroup pluginLoader
 * @{
 * @addtogroup tests
 * @{
 *
 * @date 09/04/19
 */

#include <gmock/gmock.h>

int main(int argc
         , char** argv)
{
    ::testing::InitGoogleTest(&argc
                              , argv);
    return RUN_ALL_TESTS();
}

/*! @} */
/*!
 * @brief Tests the string utility functions
 *
 * @author hmarcks
 *
 * @addtogroup utility
 *
 * @date 22/02/19
 */

#include <gtest/gtest.h>
#include <utility/utility.h>

namespace utility
{

TEST(stringUtilityTests
     , AddXLetterNormal)
{
    const int firstTest = 4;
    std::string out1 = addXLetter(firstTest
                                  , 'x');
    ASSERT_EQ(out1.size()
              , firstTest);
}

TEST(stringUtilityTests
     , AddXLetterNegative)
{
    const int firstTest = -1;
    std::string out1 = addXLetter(firstTest
                                  , 'x');
    ASSERT_EQ(out1.size()
              , 0);
}

TEST(stringUtilityTests
     , StringToLongNormal)
{
    std::string out1 = "1337";
    const long stringOut = StringToLong(out1);

    ASSERT_EQ(stringOut
              , 1337L);
}

TEST(stringUtilityTests
     , StringToLongNegative)
{
    std::string out1 = "-156";
    const long stringOut = StringToLong(out1);

    ASSERT_EQ(stringOut
              , -156L);
}

TEST(stringUtilityTests
     , StringToLongWord)
{
    std::string out1 = "AAAAA";
    const long stringOut = StringToLong(out1);

    ASSERT_EQ(stringOut
              , 0);
}
} /* namespace utility */
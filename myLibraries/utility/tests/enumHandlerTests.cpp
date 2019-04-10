/*!
 * @brief Tests the enum handler class
 *
 * @author hmarcks
 *
 * @addtogroup utility
 * @{
 * @addtogroup tests
 * @{
 *
 * @date 22/02/19
 */
 
#include <gtest/gtest.h>
#include "utility/enumHandler.h"

namespace utility
{

enum testEnum : uint8_t
{
    testEnum1, testEnum2 = 9, testEnum3
};

class EnumHandlerFixture : public ::testing::Test
{
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(EnumHandlerFixture
       , Constructor)
{
    EnumHandler<testEnum, std::string> eh;
    eh.RegisterEnum(testEnum1, "testEnum1");
    eh.RegisterEnum(testEnum2, "testEnum2");
    eh.RegisterEnum(testEnum3, "testEnum3");

    EXPECT_EQ(eh.getValue(testEnum2), "testEnum2");
    EXPECT_EQ(eh.getValue(testEnum3), "testEnum3");
    EXPECT_EQ(eh.getValue(testEnum1), "testEnum1");
}


} /* namespace utility */
/*! @} */
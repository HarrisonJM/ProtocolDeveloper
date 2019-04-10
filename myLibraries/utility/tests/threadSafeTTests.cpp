/*!
 * @brief Unit tests for the threadsafeT class
 *
 * @author hmarcks
 *
 * @addtogroup utility
 * @{
 * @addtogroup tests
 * @{
 * @date 22/02/19
 */

#include <gtest/gtest.h>
#include <utility/threadSafeT.h>

namespace utility
{

template<typename T>
class threadSafeTFixture
    : public ::testing::Test
{
public:
};

using MyTypes = ::testing::Types<char, int, long, unsigned, short>;
TYPED_TEST_SUITE(threadSafeTFixture
                 , MyTypes);

TYPED_TEST(threadSafeTFixture
           , test1)
{
    ThreadSafeT<TypeParam> Type(3);
    EXPECT_EQ(Type.GetT()
              , 3);

    Type.SetT(Type.GetT() + 1);
    EXPECT_EQ(Type.GetT()
              , 4);
}

} /* namespace Utility */

/*! @} */

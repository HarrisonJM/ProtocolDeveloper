/*!
 * @brief tests for the logger strategy
 *
 * @author hmarcks
 *
 * @addtogroup logger
 * @{
 * @addtogroup logger
 * @{
 *
 * @date 09/04/19
 */

#include <gtest/gtest.h>

#include <../src/LogHandlerStrategy.h>

class strategyFixture
    : public ::testing::Test
{
protected:

};

TEST_F(strategyFixture
       , constructor)
{
    /*public:
    //! Constructor
    explicit LogHandlerStrategy() = default;
    //! Switchcase, strategy selector
    std::unique_ptr<std::ostream> returnOstream(StrategyEnums strat
                                                , const std::string& fileName) const override;*/

    logger::LogHandlerStrategy lh;
}

TEST_F(strategyFixture
       , fstream_test)
{
    logger::LogHandlerStrategy lh;
    auto foo = lh.returnOstream(logger::StrategyEnums::FSTREAM, ".");
    EXPECT_TRUE(foo.get());
}

TEST_F(strategyFixture
       , sstream_test)
{
    logger::LogHandlerStrategy lh;
    auto foo = lh.returnOstream(logger::StrategyEnums::SSTREAM, "");
    EXPECT_TRUE(foo.get());
}

TEST_F(strategyFixture
       , stdcout_test)
{
    logger::LogHandlerStrategy lh;
    auto foo = lh.returnOstream(logger::StrategyEnums::STDOUT, "");
    EXPECT_TRUE(foo.get());
}

TEST_F(strategyFixture
       , stdcerr_test)
{
    logger::LogHandlerStrategy lh;
    auto foo = lh.returnOstream(logger::StrategyEnums::STDERR, "");
    EXPECT_TRUE(foo.get());
}

/*! @} @} */

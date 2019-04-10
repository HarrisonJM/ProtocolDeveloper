/*!
 * @brief Tests for the LogHandler class
 *
 * @author hmarcks
 * @date 10/04/19
 *
 * @addtogroup logger
 * @{
 * @addtogroup tests
 * @{
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "logger/LogHandler.h"
#include "logger/loggerUtility.h"
#include "mockLibrary/LogStrategyMocks.h"
#include "../src/LogHandlerStrategy.h"

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Return;

namespace logger
{
class LogHandlerTests : public ::testing::Test
{
protected:
    std::string _path = "";
    int _maxLogs = 5;

    void SetUp() override
    {
        logger::LogHandler::GetInstance(_maxLogs
                                               , _path);
    }

    void TearDown() override
    {
        GetInstance().FlushMessagesToStreams();
    }

    auto GetInstance() -> decltype(logger::LogHandler::GetInstance(_maxLogs
                                                                         , _path))
    {
        return logger::LogHandler::GetInstance(_maxLogs
                                                      , _path);
    }
};

TEST_F(LogHandlerTests
       , constructor_01)
{
    GetInstance().KillHandler();

    std::unique_ptr<I_LogStrategy> ilo;
    logger::LogHandler::GetInstance(_maxLogs
                                           , _path
                                           , std::move(ilo));

    ASSERT_TRUE(true);
}

TEST_F(LogHandlerTests
       , openNewLogWithoutEIS_02)
{
    GetInstance().KillHandler();
    int64_t logID = GetInstance().OpenNewLog("testLog"
                                            , StrategyEnums::STDOUT);
    EXPECT_NE(logID
              , -1);

    auto log = GetInstance().GetLogFileByID(logID);

    GetInstance().AddMessageToLog(logID
                                 , "TEST MESSAGE"
                                 , logLevel::INFO);
    GetInstance().AddMessageToLog("testLog"
                                  , "TEST MESSAGE"
                                  , logLevel::INFO);
    GetInstance().KillHandler();
    log->WriteAllMessagesToStream();
    GetInstance().CloseLog(logID);
}

} /* namespace logger */

/*! @} @} */
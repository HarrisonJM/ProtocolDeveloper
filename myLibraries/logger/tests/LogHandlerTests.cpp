/*!
 * @brief Tests for the LogHandler class
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

namespace LoggerClasses
{
class LogHandlerTests : public ::testing::Test
{
protected:
    std::string _path = "";
    int _maxLogs = 5;

    void SetUp() override
    {
        LoggerClasses::LogHandler::GetInstance(_maxLogs
                                               , _path);
    }

    void TearDown() override
    {

    }

    auto GetInstance() -> decltype(LoggerClasses::LogHandler::GetInstance(_maxLogs
                                                                         , _path))
    {
        return LoggerClasses::LogHandler::GetInstance(_maxLogs
                                                      , _path);
    }
};

TEST_F(LogHandlerTests
       , constructor_01)
{
    GetInstance().KillHandler();
    ASSERT_TRUE(true);
}

TEST_F(LogHandlerTests
       , openNewLogWithoutEIS_02)
{
    int64_t logID = GetInstance().OpenNewLog("testLog"
                                            , StrategyEnums::FSTREAM);
    EXPECT_NE(logID
              , -1);

    auto log = GetInstance().GetLogFileByID(logID);

    GetInstance().AddMessageToLog(logID
                                 , "TEST MESSAGE"
                                 , logLevel::INFO);
    testing::internal::CaptureStdout();
    log->WriteAllMessagesToStream();
    GetInstance().CloseLog(logID);
    GetInstance().KillHandler();
}

} /* namespace LoggerClasses */
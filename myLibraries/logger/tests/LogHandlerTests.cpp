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

namespace LoggerClasses {
class LogHandlerTests : public ::testing::Test
{
protected:
    std::string _path = "";
    int _maxLogs = 5;
    LogHandler *lh;
    void SetUp() override
    {
        lh = new LogHandler(_maxLogs,
                            _path);
    }
    void TearDown() override
    {

    }
};

TEST_F(LogHandlerTests,
       constructor)
{
    lh->KillHandler();
    ASSERT_TRUE(true);
}

TEST_F(LogHandlerTests,
       openNewLogWithoutEIS)
{
    int64_t logID = lh->OpenNewLog("testLog",
                                   StrategyEnums::FSTREAM);
    EXPECT_NE(logID,
              -1);

    auto log = lh->GetLogFileID(logID);

    lh->AddMessageToLog(logID,
                        "TEST MESSAGE",
                        logLevel::INFO);

    testing::internal::CaptureStdout();
    log->WriteAllMessagesToStream();
    std::string out = testing::internal::GetCapturedStdout();

    std::cout << log->ReturnLatestMessage() << std::endl;

    std::cout << "BLAH: " << out << std::endl;

    lh->KillHandler();
}

} /* namespace LoggerClasses */
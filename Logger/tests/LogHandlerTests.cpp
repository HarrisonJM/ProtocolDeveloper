//
// Created by hmarcks on 04/02/18.
//

#include "../LogHandler.h"
#include "gtest/gtest.h"

namespace Logging
{
    class LogHandlerTests : public ::testing::Test
    {
    protected:
        LogHandler *logHandler;
        std::string testLogName = "test";
        std::string logMessage = "This is a test message";
        std::string logName = "This is the name of the test";

        void SetUp()
        {
            logHandler = new LogHandler();
        };

        void TearDown()
        {
            delete logHandler;
        }

        std::map<std::string, ILog*> CheckMap()
        {
            return logHandler->openLogs;
        }

        void OpenLog()
        {
            logHandler->OpenLog("test");
        }

        bool getkillHandler()
        {
            return logHandler->killHandler;
        }

        int getNumberOfOpenLogs()
        {
            return logHandler->openLogs.size();
        }

    };

    TEST_F(LogHandlerTests, test_OpenLog)
    {
        OpenLog();

        std::map<std::string, ILog*> logmap = CheckMap();

        if(logmap["test"])
            GTEST_SUCCEED();
        else
            GTEST_FAIL();
    }

    TEST_F(LogHandlerTests, test_AddLog)
    {
        OpenLog();
        int res = logHandler->AddLog(testLogName, INFO, logMessage, logName);

        ASSERT_EQ(res, 1);
    }

    TEST_F(LogHandlerTests, test_getSetKillHandlerTrueReturn)
    {
        OpenLog();
        ASSERT_EQ(getkillHandler(), false);
        ASSERT_EQ(logHandler->getSetKillHandler(true), false);
    }

    TEST_F(LogHandlerTests, test_getSetKillHandlerModifyValue)
    {
        OpenLog();
        ASSERT_EQ(getkillHandler(), false);
        ASSERT_EQ(logHandler->getSetKillHandler(false), true);
    }

    TEST_F(LogHandlerTests, test_closeAllLogs)
    {
        OpenLog();
        logHandler->OpenLog("123");
        logHandler->OpenLog("124");
        logHandler->OpenLog("125");
        logHandler->OpenLog("126");

        ASSERT_EQ(getNumberOfOpenLogs(), 5);

        logHandler->closeAllLogs();

        ASSERT_EQ(getNumberOfOpenLogs(), 0);
    }

}
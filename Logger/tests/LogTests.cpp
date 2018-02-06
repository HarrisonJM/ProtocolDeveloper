#include "../Log.h"
#include "gtest/gtest.h"

namespace Logging
{
    class LogTests: public ::testing::Test
    {
    protected:

        Log *log;

        void SetUp() override
        {
            log = new Log("test");
        }

        void addLogToQueue(int numberOfMessages)
        {
            for (int i = 0; i < numberOfMessages; ++i)
            {
                log->AddLog(INFO,
                            "Test Message# " + i,
                            "Test Name# " + i);
            }
        }

        std::string getLogPath()
        {
            return log->logPath;
        }

        // Returns the numberOfEntriesMember
        unsigned int getNumberOfEntries()
        {
            return log->numberOfEntries;
        }

        Utility::SafeQueue<std::string>* getLogEntryQueue()
        {
            return &(log->logEntryQueue);
        }

        bool isLogFileEnded()
        {
            return log->CheckLogAlreadyEnded();
        }

        bool logQueueIsFull()
        {
            return log->queueNeedsEmptying;
        }

        void TearDown() override
        {
            log->FlushQueueToFile();
            delete log;
        }

    };

    TEST_F(LogTests, test_ConstructorgetLogKey)
    {
        EXPECT_EQ("test", log->getLogKey());
    }

    TEST_F(LogTests, test_AddLog)
    {
        addLogToQueue(1);

        EXPECT_EQ(getLogEntryQueue()->size(), 1);
    }

    TEST_F(LogTests, test_countNumberOfEntries)
    {
        addLogToQueue(1);
        ASSERT_EQ(getNumberOfEntries(), 1);

        addLogToQueue(1);
        ASSERT_EQ(getNumberOfEntries(), 2);

        addLogToQueue(3);
        ASSERT_EQ(getNumberOfEntries(), 5);
    }

    TEST_F(LogTests, test_FlushQueueToFile)
    {
        addLogToQueue(10);
        EXPECT_EQ(getNumberOfEntries(), 10);

        log->FlushQueueToFile();
        EXPECT_TRUE(getLogEntryQueue()->empty());
    }

    TEST_F(LogTests, test_hasLogBeenEnded)
    {
        log->EndLog();
        ASSERT_FALSE(isLogFileEnded());
    }

    TEST_F(LogTests, test_doesTheQueueNeedEmptying)
    {
        addLogToQueue(19);
        ASSERT_FALSE(logQueueIsFull());

        addLogToQueue(1);
        ASSERT_FALSE(logQueueIsFull());

        addLogToQueue(1);
        ASSERT_TRUE(logQueueIsFull());

    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);

        return RUN_ALL_TESTS();
    }
}
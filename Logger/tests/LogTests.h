#ifndef __TESTSTUDENT_H__
#define __TESTSTUDENT_H__

#include "../Log.h"
#include "../LoggerDefinitions.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace Logging
{
    class LogFixture : public ::testing::Test
    {
    protected:
        // The default log object the tests will be using
        Log *log;

        virtual void SetUP()
        {
            log = new Log(L"test");
        }

        virtual void TearDown()
        {
            delete log;
        }

        void AddMessages(int numberOfMessages)
        {
            for(int i = 0; i < numberOfMessages; ++i)
            {
                log->AddLog(TRIVIAL, L"Test message " + i, L"Test name " + i);
            }
        }

    };
}
#endif /* __TESTSTUDENT_H__ */

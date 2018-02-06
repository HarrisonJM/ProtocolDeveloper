#pragma once

#include "Logger/LogHandler.h"
#include <string>
#include <chrono>

extern Logging::LogHandler logHandler;

namespace TestProc
{
    class Processor
    {
    public:
        Processor(std::string in_ln,
                  std::chrono::milliseconds in_mil) :
            testName(in_ln),
            sleepTime(in_mil)
        {
            logHandler.OpenLog(testName);
        }

        ~Processor()
        {
            // More blegh
        }

        void GenerateLogMessages(std::string message)
        {
            int i = 0;
            while (i < 10000)
            {
                std::this_thread::sleep_for(sleepTime);
                logHandler.AddLog(testName, 
                                  Logging::INFO, 
                                  message, 
                                  "Test");
                ++i;
            }
        }

    private:
        std::string testName;
        std::chrono::milliseconds sleepTime;
    };
}

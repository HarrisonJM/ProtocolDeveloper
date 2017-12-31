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
        Processor(std::wstring in_ln,
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

        void GenerateLogMessages(std::wstring message)
        {
            int i = 0;
            while (i < 10000)
            {
                std::this_thread::sleep_for(sleepTime);
                logHandler.AddLog(testName, 
                                  Logging::INFO, 
                                  message, 
                                  L"Test");
                ++i;
            }
        }

    private:
        std::wstring testName;
        std::chrono::milliseconds sleepTime;
    };
}

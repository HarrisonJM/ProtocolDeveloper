
#include "Logger/LogHandler.h"
#include <thread>
#include <iostream>
#include "Processor.h"

Logging::LogHandler logHandler;

int main(int argc, char** argv)
{
    std::cout << "Hello!" << std::endl;
    logHandler.OpenLog("Jerry");

    std::thread logThread(&Logging::LogHandler::flushLogs, &logHandler);

    // Create "processors"
    TestProc::Processor p1("P1", std::chrono::milliseconds(25));
    TestProc::Processor p12("P1", std::chrono::milliseconds(50));

    TestProc::Processor p2("P2", std::chrono::milliseconds(100));
    TestProc::Processor p3("P3", std::chrono::milliseconds(150));

    TestProc::Processor p4("P4", std::chrono::milliseconds(225));
    TestProc::Processor p42("P4", std::chrono::milliseconds(250));
    TestProc::Processor p43("P4", std::chrono::milliseconds(275));

    TestProc::Processor p5("P5", std::chrono::milliseconds(250));
    TestProc::Processor p6("P6", std::chrono::milliseconds(300));

    // Spawn threads
    std::thread proc1(&TestProc::Processor::GenerateLogMessages, p1, "P1");
    proc1.detach();
    std::thread proc12(&TestProc::Processor::GenerateLogMessages, p12, "P12");
    proc12.detach();

    std::thread proc2(&TestProc::Processor::GenerateLogMessages, p2, "P2");
    proc2.detach();

    std::thread proc3(&TestProc::Processor::GenerateLogMessages, p3, "P3");
    proc3.detach();

    std::thread proc4(&TestProc::Processor::GenerateLogMessages, p4, "P4");
    proc4.detach();
    std::thread proc42(&TestProc::Processor::GenerateLogMessages, p42, "P42");
    proc42.detach();
    std::thread proc43(&TestProc::Processor::GenerateLogMessages, p43, "P43");
    proc43.detach();

    std::thread proc5(&TestProc::Processor::GenerateLogMessages, p5, "P4");
    proc5.detach();

    std::thread proc6(&TestProc::Processor::GenerateLogMessages, p6, "P5");
    proc6.detach();

    long stop = 0;
    while (stop < 100000000000000)
    {
        stop++;
    }
    
	return 0;
}

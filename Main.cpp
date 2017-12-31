
#include "Logger/LogHandler.h"
#include <thread>
#include <iostream>
#include "Processor.h"

Logging::LogHandler logHandler;

int main(int argc, char** argv)
{
    logHandler.OpenLog(L"Jerry");

    std::thread logThread(&Logging::LogHandler::flushLogs, &logHandler);

    // Create"processors"
    TestProc::Processor p1(L"P1", std::chrono::milliseconds(25));
    TestProc::Processor p12(L"P1", std::chrono::milliseconds(50));

    TestProc::Processor p2(L"P2", std::chrono::milliseconds(100));
    TestProc::Processor p3(L"P3", std::chrono::milliseconds(150));

    TestProc::Processor p4(L"P4", std::chrono::milliseconds(225));
    TestProc::Processor p42(L"P4", std::chrono::milliseconds(250));
    TestProc::Processor p43(L"P4", std::chrono::milliseconds(275));

    TestProc::Processor p5(L"P5", std::chrono::milliseconds(250));
    TestProc::Processor p6(L"P6", std::chrono::milliseconds(300));

    // Spawn threads
    std::thread proc1(&TestProc::Processor::GenerateLogMessages, p1, L"P1");
    proc1.detach();
    std::thread proc12(&TestProc::Processor::GenerateLogMessages, p12, L"P12");
    proc12.detach();

    std::thread proc2(&TestProc::Processor::GenerateLogMessages, p2, L"P2");
    proc2.detach();

    std::thread proc3(&TestProc::Processor::GenerateLogMessages, p3, L"P3");
    proc3.detach();

    std::thread proc4(&TestProc::Processor::GenerateLogMessages, p4, L"P4");
    proc4.detach();
    std::thread proc42(&TestProc::Processor::GenerateLogMessages, p42, L"P42");
    proc42.detach();
    std::thread proc43(&TestProc::Processor::GenerateLogMessages, p43, L"P43");
    proc43.detach();

    std::thread proc5(&TestProc::Processor::GenerateLogMessages, p5, L"P4");
    proc5.detach();

    std::thread proc6(&TestProc::Processor::GenerateLogMessages, p6, L"P5");
    proc6.detach();
    
    while (1);

	return 0;
}
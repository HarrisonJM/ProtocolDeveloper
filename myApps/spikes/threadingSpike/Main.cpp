#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

void workerFuncArg(const char* msg, unsigned delaySecs) //...
{
    boost::posix_time::seconds workTime(delaySecs);

    std::cout << msg << std::endl;

    // Pretend to do something useful...
    boost::this_thread::sleep(workTime);

    std::cout << "Worker: finished" << std::endl;
}

void workerFunc()
{
    boost::posix_time::seconds workTime(3);

    std::cout << "GRRR" << std::endl;

    // Pretend to do something useful...
    boost::this_thread::sleep(workTime);

    std::cout << "Worker: finished" << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "main: startup" << std::endl;

    boost::thread workerFuncArg(workerFunc, "Hello, boost! penis", 3);
    boost::thread workerThread(workerFunc);

    std::cout << "main: waiting for thread" << std::endl;

    workerThread.join();

    std::cout << "main: done" << std::endl;

    return 0;
}
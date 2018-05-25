/*!
 * @brief Due to the nature fo what is being tested and how it's been implemented,
 * the thread pool cannot be mocked so will only be unit tested. By proxy of public
 * interface and high coupling, the WorkerThread class is unit tested too
 */

#include <functional>
#include "gtest/gtest.h"
#include "../ThreadPool.h"
#include <sys/prctl.h>

namespace ThreadHandler
{

// Just returns a number
int aFunctionToRun0()
{
    return 909;
}

// Returns an increment of C
char aFunctionToRun1(char c)
{
    return ++c;
}

// Appends a string to a string reference
void aFunctionToRun2( std::string& str, const std::string append)
{
    str += append;
}

// Testing void pointers (What I'm considering to be real data)
void aFunctionToRunReal(void* data,
                        const unsigned int dataSize)
{
    const char* str = "BY THE POWER OF GRAY SKULL";
    memcpy(data, str, dataSize);
}


class ThreadPool_Tests: public ::testing::Test
{
public:

    ThreadPool *testPool = nullptr;

    void SetUp() override
    {
        prctl(PR_SET_NAME,
              ::testing::UnitTest::GetInstance()->current_test_info()->name(),
              0,0,0);
    }

    void TearDown() override
    {
        delete testPool;
    }
};


TEST_F(ThreadPool_Tests,
       Constructor)
{
    // Proper
    testPool = new ThreadPool(1);
    // Default
    testPool = new ThreadPool();
}

TEST_F(ThreadPool_Tests, initPool)
{
    testPool = new ThreadPool(1);
    testPool->InitPool();
}

TEST_F(ThreadPool_Tests, submitTask_0)
{
    testPool = new ThreadPool(1);
    testPool->InitPool();

    auto future = testPool->AddTaskToQueue(aFunctionToRun0);

    const int result = future.get();
    EXPECT_EQ(909, result);
}

} /* namespace ThreadHandler */
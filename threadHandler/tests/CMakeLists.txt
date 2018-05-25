
set(CMAKE_CXX_FLAGS "-std=gnu++14 -lpthread -ldl -Wall -pthread")

add_executable(threadHandlerTests
        ../ThreadPool.cpp
        ../WorkerThread.cpp
        ThreadPool_Tests.cpp)

target_link_libraries(threadHandlerTests
        freeFunctionMocks
        gtest
        gtest_main)
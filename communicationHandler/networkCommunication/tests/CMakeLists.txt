
add_executable(netCommTest
        ../NetworkCommunication.cpp
        networkCommunication_Tests.cpp)

target_link_libraries(netCommTest
        freeFunctionMocks
        NetworkCommunication
        gtest
        gtest_main)
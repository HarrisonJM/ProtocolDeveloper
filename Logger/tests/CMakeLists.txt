##tests
# Now simply link against gtest or gtest_main as needed. Eg
add_executable(LogTests LogTests.cpp LogHandlerTests.cpp)
target_link_libraries(LogTests
        Logger
        gtest
        gtest_main
        TimeGeneration)
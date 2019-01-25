# Define library. Only source files here!
project(threadPool VERSION 0.1 LANGUAGES CXX)

add_library(threadPool
        src/ThreadPool.cpp
        src/WorkerThread.cpp)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(threadPool PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# If we have compiler requirements for this library, list them
# here
#target_compile_features(lib
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(threadPool
                      safeContainers) ## Insert libraries as needed

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS     threadPool
        EXPORT      threadPoolConfig
        ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY   include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT      threadPoolConfig
        DESTINATION share/MyLibraries/cmake)

# This makes the project importable from the build directory
export( TARGETS      threadPool
        FILE         threadPoolConfig.cmake)

add_executable(testThreadPool
        tests/ThreadPool_Tests.cpp)
target_link_libraries(testThreadPool
        threadPool
        gtest_main
        gtest)

add_test(testThreadPool testThreadPool)
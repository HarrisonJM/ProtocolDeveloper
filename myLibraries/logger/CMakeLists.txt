# Define library. Only source files here!
project(logger VERSION 0.1 LANGUAGES CXX)

add_library(logger
        src/LogHandlerStrategy.cpp
        src/LogFile.cpp
        src/LogHandler.cpp
        src/loggerExceptions.h)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(logger PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# If we have compiler requirements for this library, list them
# here
#target_compile_features(lib
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(logger
        enumHandler
        safeQueues
        utilityFunctions
        threadPool
        mockLibrary)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS     logger
        EXPORT      loggerConfig
        ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY   include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT      loggerConfig
        DESTINATION share/MyLibraries/cmake)

# This makes the project importable from the build directory
export(TARGETS      logger
       FILE         loggerConfig.cmake)

# Every library has unit tests, of course
add_executable(testLogger
               tests/loggerTestsMain.cpp
               tests/LogFileTests.cpp
               tests/LogHandlerTests.cpp
               src/LogHandlerStrategy.cpp)
target_link_libraries(testLogger
                      logger
                      gmock
                      gmock_main
                      gtest_main
                      gtest)

add_test(testLogger testLogger)

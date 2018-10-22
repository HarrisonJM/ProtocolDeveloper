# Define library. Only source files here!
project(testCaseAnalyser VERSION 0.1 LANGUAGES CXX)

add_library(testCaseAnalyser
        src/dataEmitter.cpp
        src/dataPoint.cpp
        src/mathsModule.cpp
        src/dataPoint.cpp
        src/operation.cpp
        src/testCaseCompiler.cpp
        src/testCaseParser.cpp
        src/variable.cpp
        src/opVarBase.cpp )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(testCaseAnalyser PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# If we have compiler requirements for this library, list them
# here
#target_compile_features(lib
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(testCaseAnalyser
        ) ## Insert libraries as needed

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS     testCaseAnalyser
        EXPORT      testCaseAnalyserConfig
        ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY   include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT      testCaseAnalyserConfig
        DESTINATION share/MyLibraries/cmake)

# This makes the project importable from the build directory
export( TARGETS      testCaseAnalyser
        FILE         testCaseAnalyserConfig.cmake)

# Every library has unit tests, of course
add_executable( testTestCaseAnalyser
        tests/testCaseAnalyserTests.cpp)
target_link_libraries(testTestCaseAnalyser
        testCaseAnalyser
        gtest_main
        gtest)

add_test(testTestCaseAnalyser testTestCaseAnalyser)
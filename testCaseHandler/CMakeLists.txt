add_library(testCaseAnalyser
        mathsModule.cpp
        variable.cpp
        dataPoint.cpp
        dataEmitter.cpp
        testCaseParser.cpp
        testCaseCompiler.cpp
        S_testCaseConfiguration.h
        operations.cpp operations.h testCaseException.h)

link_libraries(testCaseAnalyser
        utility)

add_subdirectory(tests)
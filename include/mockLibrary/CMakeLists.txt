add_library(freeFunctionMocks
        cNetCommMocks.h
        cStdLibMocks.h)

target_link_libraries(freeFunctionMocks
        gmock)



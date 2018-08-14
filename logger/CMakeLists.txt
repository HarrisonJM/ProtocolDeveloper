add_subdirectory(tests)

add_library (logger SHARED LogFile.cpp LogHandler.cpp LogHandler.h)

target_link_libraries(logger
        threadHandler)

configure_file(I_LogFile.h ${CMAKE_SOURCE_DIR}/include/interfaces/)


add_library(threadHandler
        ThreadPool.cpp
        WorkerThread.cpp)

configure_file(I_ThreadPool.h
        ${CMAKE_SOURCE_DIR}/include/interfaces/I_ThreadPool.h)

add_subdirectory(tests)
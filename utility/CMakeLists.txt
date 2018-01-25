add_library(timeGeneration timeGeneration.cpp)

add_subdirectory(tests)

configure_file(SafeQueue.h ${CMAKE_SOURCE_DIR}/include/SafeQueue.h)
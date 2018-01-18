cmake_minimum_required(VERSION 3.9.6)
# Project must go here
project(ProtocolDeveloper)

include(CTest)

set(CMAKE_CXX_FLAGS "-std=gnu++14 -lpthread -Wall")

include_directories(include/)
link_directories(lib)

add_subdirectory(Logger)
add_subdirectory(utility timeGeneration)

add_executable(ProtocolDeveloper Main.cpp)
target_link_libraries(ProtocolDeveloper Logger timeGeneration)

cmake_minimum_required(VERSION 3.9.6)
# Project must go here
project(ProtocolDeveloper)
set(CMAKE_CXX_FLAGS "-std=gnu++14 -lpthread -Wall")

include_directories(common)

add_subdirectory(common)
add_subdirectory(Logger)
add_subdirectory(utility timeGeneration)

add_executable(ProtocolDeveloper Main.cpp)

target_link_libraries(ProtocolDeveloper Logger timeGeneration)


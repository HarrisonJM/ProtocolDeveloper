cmake_minimum_required(VERSION 3.9.6)
## Project must go here #
project(ProtocolDeveloper LANGUAGES CXX VERSION 0.1 )
set(CMAKE_CXX_FLAGS "-std=gnu++17 -std=c++17 -lpthread -ldl -Wall")

# The following is to acquire a new version of gmock/gtest
# at confgiure time. Will also build
##########################################################
## FOLLOWING WRITTEN BY GOOGLE ##
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
## END GTEST PART ##
##########################################################

## Example of including a seperate package for the project
# Include Boost as an imported target

find_package(Boost REQUIRED system)

# https://gist.github.com/dennycd/5890475 <-- building boost with c++17 flags
if (Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    add_library(boost INTERFACE IMPORTED)
    set_property(TARGET boost PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
endif ()

## Adding the Mongo driver libraries
## Add Mongo
#find_package(libmongocxx REQUIRED)
#   find_package(libbsoncxx REQUIRED)

## List all newly created, personal, projects/libraries here
#find_package(freeFunctionsAndWrappers REQUIRED)

## Manually adding the gtest/gmock include directories
include_directories("${gtest_SOURCE_DIR}/include")
include_directories("${gmock_SOURCE_DIR}/include")

include(GNUInstallDirs)

#include_directories("otherLibraries/boost/include/")
#link_directories("otherLibraries/boost/lib/")

## Targets
enable_testing()

add_subdirectory(myLibraries)
add_subdirectory(myApps)

# Project organisation based on https://rix0r.nl/blog/2015/08/13/cmake-guide/ ->
# -> this was used as a way to better codify and neaten up many of
# my directories and CMakeLists files.
cmake_minimum_required(VERSION 3.14.1)
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
include(ExternalProject)

# Builds gRPC based on locally checked-out sources and set arguments so that all the dependencies
# are correctly located.
ExternalProject_Add(grpc
                    PREFIX grpc
                    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/otherLibraries/grpc"
                    CMAKE_CACHE_ARGS
                    -DgRPC_INSTALL:BOOL=ON
                    -DgRPC_BUILD_TESTS:BOOL=OFF
                    -DgRPC_PROTOBUF_PROVIDER:STRING=package
                    -DgRPC_PROTOBUF_PACKAGE_TYPE:STRING=CONFIG
                    -DProtobuf_DIR:PATH=${_FINDPACKAGE_PROTOBUF_CONFIG_DIR}
                    -DgRPC_ZLIB_PROVIDER:STRING=package
                    -DZLIB_ROOT:STRING=${CMAKE_CURRENT_BINARY_DIR}/otherLibraries/zlib
                    -DgRPC_CARES_PROVIDER:STRING=package
                    -Dc-ares_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/otherLibraries/c-ares/lib/cmake/c-ares
                    -DgRPC_SSL_PROVIDER:STRING=package
                    ${_CMAKE_ARGS_OPENSSL_ROOT_DIR}
                    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/grpc
                    DEPENDS c-ares protobuf zlib
                    )

find_package(Boost REQUIRED system)

# https://gist.github.com/dennycd/5890475 <-- building boost with c++17 flags
if (Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    add_library(boost INTERFACE IMPORTED)
    set_property(TARGET boost PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
endif ()

find_package(Protobuf REQUIRED system)
if (Protobuf_FOUND)
    message(STATUS "Protobus Version: " ${Protobuf_VERSION})
    include_directories(${Protobuf_INCLUDE_DIRS})
endif()

# Adding the Mongo driver libraries
# Add Mongo
find_package(Mongocxx REQUIRED)
   find_package(Bsoncxx REQUIRED)

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
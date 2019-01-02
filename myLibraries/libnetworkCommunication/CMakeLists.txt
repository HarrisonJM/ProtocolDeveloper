# Define library. Only source files here!
project(libnetworkCommunication VERSION 0.1 LANGUAGES CXX)
set(LIB_NAME "libnetworkCommunication")

add_library(${LIB_NAME}
        src/libNetworkCommunication.cpp
        )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(${LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# If we have compiler requirements for this library, list them
# here
#target_compile_features(lib
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(${LIB_NAME}
        communicationHandler
        freeFunctionsAndWrappers
        ) ## Insert libraries as needed

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}Config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ${LIB_NAME}Config
        DESTINATION share/MyLibraries/cmake)

# This makes the project importable from the build directory
export(TARGETS ${LIB_NAME}
        FILE ${LIB_NAME}Config.cmake)

# Every library has unit tests, of course
add_executable(testNetworkCommunication
        tests/networkCommunication_Tests.cpp)
target_link_libraries(testNetworkCommunication
        ${LIB_NAME}
        mockLibrary
        gtest_main
        gtest
        gmock
        gmock_main)

add_test(testNetworkCommunication testNetworkCommunication)
# Define library. Only source files here!
project(enumHandler VERSION 0.1 LANGUAGES CXX)

add_library(enumHandler INTERFACE)
target_sources(enumHandler INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(enumHandler INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

# If we have compiler requirements for this library, list them
# here
#target_compile_features(lib
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(enumHandler
        ) ## Insert libraries as needed

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS enumHandler
        EXPORT enumHandlerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT enumHandlerConfig
        DESTINATION share/MyLibraries/cmake)

# This makes the project importable from the build directory
export(TARGETS enumHandler
        FILE enumHandlerConfig.cmake)

# Every library has unit tests, of course
add_executable(testEnumHandler
        tests/enumHandlerTests.cpp)
target_link_libraries(testEnumHandler
        enumHandler
        gtest_main
        gtest)

add_test(testEnumHandler testEnumHandler)
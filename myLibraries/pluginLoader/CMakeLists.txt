# Define library. Only source files here!
project(pluginLoader VERSION 0.1 LANGUAGES CXX)

add_library(pluginLoader
            src/pluginLoader.cpp
            include/pluginLoader/pluginLoader.h
            src/pluginLoaderTemplate.h
            include/pluginLoader/PluginLoaderCommon.h
            include/I_plugin.h
            src/pluginLoaderTemplate.cpp
            src/pluginLoaderTemplate.h
            src/dllAbstract.h
            include/I_dllAbstract.h
            src/pluginLoader_exception.h include/I_pluginLoaderTemplate.h)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(pluginLoader PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)

# If we have compiler requirements for this library, list them
# here
#target_compile_features(pluginLoader
#        PUBLIC cxx_std_17
#        PRIVATE cxx_std_17)

# Depend on a library that we defined in the top-level file
target_link_libraries(pluginLoader
                      stdc++fs # The C++ filesystem library
                      boost_system
                      boost_filesystem
                      freeFunctionsAndWrappers
                      testAnalyser2
                      magic
                      ) ## Insert libraries as needed

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS pluginLoader
        EXPORT pluginLoaderConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT pluginLoaderConfig
        DESTINATION share/MyLibraries/cmake)

# This makes the project importable from the build directory
export(TARGETS pluginLoader
       FILE pluginLoaderConfig.cmake)

# Every library has unit tests, of course
add_executable(testPluginLoader
               tests/pluginLoaderTestsMain.cpp
               tests/pluginLoaderTests.cpp)
target_link_libraries(testPluginLoader
                      pluginLoader
                      Boost::system
                      gtest_main
                      gtest)

add_test(testPluginLoader testPluginLoader)
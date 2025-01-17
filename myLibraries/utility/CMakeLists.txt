# Define library. Only source files here!
project(utility VERSION 0.1 LANGUAGES CXX)
set(LIB_NAME "utility")

add_library(${LIB_NAME}
            src/stringUtility.cpp
            include/utility/threadSafeT.h
            include/utility/enumHandler.h include/utility/extraExceptionBase.h)

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

add_executable(test${LIB_NAME}
               tests/${LIB_NAME}Tests.cpp
               tests/stringUtilityTests.cpp
               tests/enumHandlerTests.cpp
               tests/threadSafeTTests.cpp
               include/utility/extraExceptionBase.h)
target_link_libraries(test${LIB_NAME}
                      ${LIB_NAME}
                      gtest_main
                      gtest)

add_test(test${LIB_NAME} test${LIB_NAME})
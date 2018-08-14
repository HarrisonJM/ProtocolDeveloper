
add_library(UtilityFunctions stringUtility.cpp)

configure_file(stringUtility.h
        ${CMAKE_SOURCE_DIR}/include/utilityFunctions/stringUtility.h)
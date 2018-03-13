add_library(TimeGeneration TimeGeneration.cpp utility.h)

configure_file(TimeGeneration.h ${CMAKE_SOURCE_DIR}/include/TimeGeneration.h)

# This will build wrapped free functions from C-libraries
add_library(cNetComm
        cNetComm.cpp)

add_library(cStdLib
        cStdLib.cpp)

configure_file(cNetComm.h ${CMAKE_SOURCE_DIR}/include/cNetComm.h)
configure_file(I_cNetComm.h ${CMAKE_SOURCE_DIR}/include/interfaces/I_cNetComm.h)

configure_file(cStdLib.h ${CMAKE_SOURCE_DIR}/include/cStdLib.h)
configure_file(I_cStdLib.h ${CMAKE_SOURCE_DIR}/include/interfaces/I_cStdLib.h)
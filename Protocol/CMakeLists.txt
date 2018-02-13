add_library(ProtocolHandler ProtocolHandler.cpp)

add_subdirectory(test)
add_subdirectory(HelloWorldProtocol)

configure_file(ProtocolInterface.h ${CMAKE_SOURCE_DIR}/include/ProtocolInterface.h)
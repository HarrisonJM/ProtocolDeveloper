
add_library(CommunicationHandler CommunicationHandler.cpp)
configure_file(CommunicationInterface.h ${CMAKE_SOURCE_DIR}/include/CommunicationInterface.h)

add_subdirectory(networkCommunication)
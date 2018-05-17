
add_library(CommunicationHandler
        communicationHandler.cpp)

configure_file(I_communication.h
        ${CMAKE_SOURCE_DIR}/include/interfaces/I_communication.h)

add_subdirectory(networkCommunication)
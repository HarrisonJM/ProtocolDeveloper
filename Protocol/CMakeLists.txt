add_library(ProtocolInterface)

add_subdirectory(test)
add_subdirectory(HelloWorldProtocol)

configure_file(ProtocolInterface.h ../include/)
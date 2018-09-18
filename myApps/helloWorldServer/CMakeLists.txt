
add_executable(HelloWorldServer
        src/HelloWorldServerMain.cpp
        src/ServerSetup.cpp
        src/BasicHello.cpp
        src/ConnectionHandler.cpp
        src/ConfigurationInterface.cpp)

target_link_libraries(HelloWorldServer
        )
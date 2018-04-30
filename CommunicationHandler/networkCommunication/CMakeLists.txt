add_library(NetworkCommunication
        NetworkCommunication.cpp)

add_executable(netCommTest main.cpp NetworkCommunication.cpp)
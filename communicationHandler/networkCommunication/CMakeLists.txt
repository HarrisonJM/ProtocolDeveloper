add_subdirectory(tests)

add_library(NetworkCommunication
        NetworkCommunication.cpp)

target_link_libraries(NetworkCommunication
        cNetComm)

add_executable(netCommTest_Manual main.cpp NetworkCommunication.cpp)

target_link_libraries(netCommTest_Manual
        cNetComm)
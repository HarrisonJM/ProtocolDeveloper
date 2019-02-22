add_executable(dllSpike2 main.cpp)

target_link_libraries(dllSpike2
                      pluginLoader
                      boost_system
                      boost_filesystem)


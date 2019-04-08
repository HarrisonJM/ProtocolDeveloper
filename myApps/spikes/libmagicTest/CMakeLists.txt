add_executable(libMagicTest
               main.cpp)

target_link_libraries(libMagicTest
                      boost_system
                      boost_filesystem
                      magic)
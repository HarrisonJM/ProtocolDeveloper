
add_executable(ProtocolDeveloper
               Main.cpp)

target_link_libraries(ProtocolDeveloper
                      logger
                      testAnalyser2
                      testRunner
                      serviceLib
                      )
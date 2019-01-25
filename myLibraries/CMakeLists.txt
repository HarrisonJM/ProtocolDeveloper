## Small and Header Only SafeContainers Libraries ##
add_subdirectory(enumHandler)
add_subdirectory(safeContainers)
add_subdirectory(utility)
add_subdirectory(mockLibrary)
add_subdirectory(freeFunctionsAndWrappers)

## Core Libraries #
add_subdirectory(logger)
add_subdirectory(pluginLoader)
add_subdirectory(testAnalyser2)
add_subdirectory(threadPool)
add_subdirectory(timeTicker)
add_subdirectory(testRunner)
add_subdirectory(database)
add_subdirectory(gRPCInterface)

add_subdirectory(testCaseAnalyser) ## Deprecated, kept just-in-case ##
#add_subdirectory(communicationHandler) ## Deprecated, Probably isn't/wasn't ever needed at all ##

## Shared Objects/Plugins ##
add_subdirectory(libnetworkCommunication)
add_subdirectory(helloWorldProtocol)

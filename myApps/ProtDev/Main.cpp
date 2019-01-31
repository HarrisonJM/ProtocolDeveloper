#include <iostream>
#include <testRunner/testRunner.h>
#include <pluginLoader/pluginLoader.h>

int main(int argc, char** argv)
{
//	TestRunner(std::string const& testfilePath
//		, const PluginLoader::sharedMap_t<
//		PluginLoader::I_Plugin<Communication::I_communication>>& commsInterfaces
//	, const PluginLoader::sharedMap_t<
//		PluginLoader::I_Plugin<Protocol::I_protocolInterface>>& protocolInterfaces
//	, std::unique_ptr<testAnalyser2::I_TestAnalyser2> TAIn
//		, ThreadHandler::ThreadPool& threadPool_in);

	//Load plugins
	PluginLoader::PluginLoader PL;
	PL.ScanForComms("/home/hmarcks/src/ProtocolDeveloper/cmake-build-debug/myLibraries/libnetworkCommunication/");
    PL.ScanForProtocols("/home/hmarcks/src/ProtocolDeveloper/cmake-build-debug/myLibraries/helloWorldProtocol/");



//	TestRunner::TestRunner tr;

	return 0;
}

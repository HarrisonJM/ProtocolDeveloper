#include <iostream>
#include <testRunner/testRunner.h>
#include <pluginLoader/pluginLoader.h>
#include <testAnalyser2/testAnalyser2.h>

int main(int argc
         , char** argv)
{
    ThreadHandler::ThreadPool pool(10);
    pool.InitPool();

//	TestRunner(std::string const& testfilePath
//		, const PluginLoader::sharedMap_t<
//		PluginLoader::I_Plugin<Communication::I_communication>>& commsInterfaces
//	, const PluginLoader::sharedMap_t<
//		PluginLoader::I_Plugin<Protocol::I_protocolInterface>>& protocolInterfaces
//	, std::unique_ptr<testAnalyser2::I_TestAnalyser2> TAIn
//		, ThreadHandler::ThreadPool& threadPool_in);

    //Load plugins
    PluginLoader::PluginLoader PL;
    PL.ScanForComms("/home/hmarcks/src/builds/protDev-debug/myLibraries/libnetworkCommunication/");
    PL.ScanForProtocols("/home/hmarcks/src/builds/protDev-debug/myLibraries/helloWorldProtocol/");

    std::string testFileName = "../../../../ProtocolDeveloper/myLibraries/testAnalyser2/sntp.xml";

    testAnalyser2::TestAnalyser2 TA2(testFileName);
    TestRunner::TestRunner tr(testFileName
                              , PL.getCommsPlugins()
                              , PL.getProtocolPlugins()
                              , std::make_unique<decltype(TA2)>(TA2)
                              , pool);
    tr.BeginTesting();
    std::cout << "Testing done" << std::endl;
    return 0;
}

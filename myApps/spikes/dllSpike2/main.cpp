/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 07/02/19
 */

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>

#include<I_plugin.h>
#include <I_communication.h>
#include <iostream>

int main()
{
    auto pluginCreator =
        boost::dll::import_alias<std::shared_ptr<PluginLoader::I_Plugin<
            Communication::I_communication>>>("/home/hmarcks/src/ProtocolDeveloper/cmake-build-debug/myLibraries/libnetworkCommunication/libnetworkCommunication.so"
                                              , "createNewPlugin"
                                              , boost::dll::load_mode::append_decorations)
            .get()->get();

    std::cout << (*pluginCreator).getPluginName() << std::endl;
}
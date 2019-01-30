/*!
 * @brief Defines how the plugin loader will behave
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date 24/12/18
 */

#include <I_communication.h>
#include <pluginLoader/pluginLoader.h>
#include "pluginLoaderTemplate.h"

namespace PluginLoader
{

PluginLoader::PluginLoader()
{
}
/*!
 * @brief Scans for all plugins in the default provided location
 * @todo Flesh out return
 * @return true on success, otherwise false
 */
bool PluginLoader::ScanForAllPluginsDefaultLoc()
{
    ScanForComms(_prefix);
    ScanForProtocols(_prefix);
//    ScanForTestCase(_prefix);
    return true;
}
/*!
 * @brief Scans for all plugins in the location provided in pathToPlugins
 * @param pathToPlugins The path to where to search for plugins
 * @return true on success, otherwise false
 */
bool PluginLoader::ScanForAllPluginsNewLoc(std::string const& pathToPlugins)
{
    ScanForComms(pathToPlugins);
    ScanForProtocols(pathToPlugins);
//    ScanForTestCase(pathToPlugins);
    return false;
}
/*!
 * @brief Scans for communication plugins in the provided folder + "comms"
 * @param pathToPlugins The path one above where the comms are located
 */
void PluginLoader::ScanForComms(std::string const& pathToPlugins)
{
    PluginLoaderTemplate<Communication::I_communication> plt(pathToPlugins
                                                             , ""
                                                             , _commsPlugins);
}

void PluginLoader::ScanForProtocols(std::string const& pathToPlugins)
{
    PluginLoaderTemplate<Protocol::I_protocolInterface> plt(pathToPlugins
                                                             , ""
                                                             , _protocolPlugins);
}
void PluginLoader::_ScanForPlugins(std::string extraQualification)
{
}
sharedMap_t<Communication::I_communication>& PluginLoader::getCommsPlugins()
{
    return _commsPlugins;
}
sharedMap_t<Protocol::I_protocolInterface>& PluginLoader::getProtocolPlugins()
{
    return _protocolPlugins;
}
} /* namespace PluginLoader */
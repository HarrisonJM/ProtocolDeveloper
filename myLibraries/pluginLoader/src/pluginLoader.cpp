/*!
 * @brief Defines how the plugin loader will behave
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 * @{
 * @date 24/12/18
 */

#include <I_communication.h>
#include <pluginLoader/pluginLoader.h>
#include "pluginLoaderTemplate.h"

namespace pluginLoader
{
/*!
 * @brief Constructor
 * @param loggerID ID of the logger it should use
 */
PluginLoader::PluginLoader(int loggerID)
    : _loggerID(loggerID)
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
                                                             , _commsPlugins
                                                             , 0);
    LOGMESSAGE("Scanning for Comms plugins"
               , logger::logLevel::INFO);
    try
    {
        plt.ScanForPlugins();
    } catch (std::exception& e)
    {
        LOGMESSAGE(e.what()
                   , logger::logLevel::ERROR);
    }

    this->_commsPlugins = plt.getPlugins();
}
/*!
 * @brief Scans for protocol plugins
 * @param pathToPlugins The path to where the plugins are located
 */
void PluginLoader::ScanForProtocols(std::string const& pathToPlugins)
{
    PluginLoaderTemplate<Protocol::I_protocolInterface> plt(pathToPlugins
                                                            , ""
                                                            , _protocolPlugins
                                                            , 0);
    LOGMESSAGE("Scanning for Protocol plugins"
               , logger::logLevel::INFO);
    try
    {
        plt.ScanForPlugins();
    } catch (std::exception& e)
    {
        LOGMESSAGE(e.what()
                   , logger::logLevel::ERROR);
    }
    this->_protocolPlugins = plt.getPlugins();
}
/*!
 * @brief Returns the sharedmap that cotnains all the comms plugins
 * @return a map of sharedptr's to comms plguins
 */
sharedMap_t<Communication::I_communication>& PluginLoader::getCommsPlugins()
{
    return _commsPlugins;
}
/*!
 * @brief Returns the sharedmap that cotnains all the protocol plugins
 * @return a map of sharedptr's to protocol plguins
 */
sharedMap_t<Protocol::I_protocolInterface>& PluginLoader::getProtocolPlugins()
{
    return _protocolPlugins;
}

} /* namespace pluginLoader */
/*! @} */
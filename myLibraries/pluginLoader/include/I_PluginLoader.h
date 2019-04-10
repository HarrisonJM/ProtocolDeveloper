/*!
 * @brief The PluginLoader interface
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 * @{
 * @addtogroup interfaces
 * @{
 * @date March 2018
 */

#ifndef PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H
#define PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H

#include <string>

namespace pluginLoader
{
class I_PluginLoader
{
public:
    /*!
     * @brief Destructor
     */
    virtual ~I_PluginLoader() = default;
    /*!
     * @brief Scans for all plugins in the default provided location
     * @todo Flesh out return
     * @return true on success, otherwise false
     */
    virtual bool ScanForAllPluginsDefaultLoc() = 0;
    /*!
     * @brief Scans for all plugins in the location provided in pathToPlugins
     * @param pathToPlugins The path to where to search for plugins
     * @return true on success, otherwise false
     */
    virtual bool ScanForAllPluginsNewLoc(std::string const& pathToPlugins) = 0;
    /*!
     * @brief Scans for communication plugins in the provided folder + "comms"
     * @param pathToPlugins The path one above where the comms are located
     */
    virtual void ScanForComms(std::string const& pathToPlugins) = 0;
    /*!
     * @brief Scans for protocol plugins
     * @param pathToPlugins The path to where the plugins are located
     */
    virtual void ScanForProtocols(std::string const& pathToPlugins) = 0;
//    void ScanForTestCase(std::string const &pathToPlugins);
};
}
/*! @} @} */
#endif //PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H

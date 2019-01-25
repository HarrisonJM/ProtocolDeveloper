/*!
 * @brief The PluginLoader interface
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date March 2018
 */

#ifndef PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H
#define PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H

#include <string>

namespace PluginLoader
{
class I_PluginLoader
{
public:
    virtual ~I_PluginLoader() = default;
    virtual bool ScanForAllPluginsDefaultLoc() = 0;
    virtual bool ScanForAllPluginsNewLoc(std::string const& pathToPlugins) = 0;
    virtual void ScanForComms(std::string const& pathToPlugins) = 0;
    virtual void ScanForProtocols(std::string const& pathToPlugins) = 0;
//    void ScanForTestCase(std::string const &pathToPlugins);
};
}
#endif //PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H

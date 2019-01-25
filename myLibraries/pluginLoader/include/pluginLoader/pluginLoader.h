/*!
 * @brief Finds, stores and provides available plugins fo ruse throughout the system
 *  Should track:
 *      Communication plugins (networks, hardware, USB, etc)
 *      @todo Protocol plugins (SNTP, LDAP, etc)
 *      @todo threadHandler plugins (Changes the branching implementation)
 *      @todo testCase plugins (Changes to how the testcases are read and handled?)
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date 24/12/18
 *
 * @todo Add plugin support fo changing the branching method
 */

#ifndef PROTOCOLDEVELOPER_PLUGINLOADER_H
#define PROTOCOLDEVELOPER_PLUGINLOADER_H

#include <map>

#include <I_communication.h>
#include <pluginLoader/PluginLoaderCommon.h>
#include <I_PluginLoader.h>
#include <I_protocolInterface.h>

namespace PluginLoader
{

class PluginLoader
    : public I_PluginLoader
{
public:
    PluginLoader();
    ~PluginLoader() override = default;
    bool ScanForAllPluginsDefaultLoc() override;
    bool ScanForAllPluginsNewLoc(std::string const& pathToPlugins) override;
    void ScanForComms(std::string const& pathToPlugins) override;
    void ScanForProtocols(std::string const& pathToPlugins) override;
//    void ScanForTestCase(std::string const &pathToPlugins) override ;

private:
    /*! @brief The prefix to where the plugins are kept i.e. /opt/ProtDev/plugins/ */
    std::string _prefix;
    /*!
     * @brief Where we'll store all loaded plugins
     * @todo Add more maps
     * @{
     */
    sharedMap_t<Communication::I_communication> _commsPlugins; /*! < Communication Plugins */
    sharedMap_t<Protocol::I_protocolInterface> _ProtocolPlugins; /*! < Protocol Plugins */
    /*!@}*/

    /*!
     * @brief No idea what the original purpose of this was...
     * @param extraQualification
     */
    void _ScanForPlugins(std::string extraQualification);
};
} /* namespace PluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINLOADER_H */

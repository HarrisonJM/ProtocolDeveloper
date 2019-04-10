/*!
 * @brief Finds, stores and provides available plugins fo ruse throughout the system
 *  Should track:
 *      Communication plugins (networks, hardware, USB, etc)
 *      Protocol plugins (SNTP, LDAP, etc)
 *      @todo threadHandler plugins (Changes the branching implementation)
 *      @todo testCase plugins (Changes to how the testcases are read and handled?)
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 * @{
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

namespace pluginLoader
{
/*!
 * @brief The public plugin loader class
 */
class PluginLoader
    : public I_PluginLoader
{
public:
    /*!
     * @brief Constructor
     * @param loggerID The ID of the logger we want it to use
     */
    explicit PluginLoader(int loggerID);
    /*!
     * @brief Destructor
     */
    ~PluginLoader() override = default;
    /*!
     * @brief Scans for all plugins in the default provided location
     * @todo Flesh out return
     * @return true on success, otherwise false
     */
    bool ScanForAllPluginsDefaultLoc() override;
    /*!
     * @brief Scans for all plugins in the location provided in pathToPlugins
     * @param pathToPlugins The path to where to search for plugins
     * @return true on success, otherwise false
     */
    bool ScanForAllPluginsNewLoc(std::string const& pathToPlugins) override;
    /*!
     * @brief Scans for communication plugins in the provided folder + "comms"
     * @param pathToPlugins The path one above where the comms are located
     */
    void ScanForComms(std::string const& pathToPlugins) override;
    /*!
     * @brief Scans for protocol plugins
     * @param pathToPlugins The path to where the plugins are located
     */
    void ScanForProtocols(std::string const& pathToPlugins) override;
    /*!
     * @brief Returns the sharedmap that cotnains all the comms plugins
     * @return a map of sharedptr's to comms plguins
     */
    sharedMap_t<Communication::I_communication>& getCommsPlugins();
    /*!
     * @brief Returns the sharedmap that cotnains all the protocol plugins
     * @return a map of sharedptr's to protocol plguins
     */
    sharedMap_t<Protocol::I_protocolInterface>& getProtocolPlugins();
private:
    const long _loggerID;
    /*! @brief The prefix to where the plugins are kept i.e. /opt/ProtDev/plugins/ */
    std::string _prefix;
    /*!
     * @brief Where we'll store all loaded plugins
     * @todo Add more maps
     * @{
     */
    sharedMap_t<Communication::I_communication> _commsPlugins; /*! < Communication Plugins */
    sharedMap_t<Protocol::I_protocolInterface> _protocolPlugins; /*! < Protocol Plugins */
    /*!@}*/
};
} /* namespace pluginLoader */
/*! @} */
#endif /* PROTOCOLDEVELOPER_PLUGINLOADER_H */

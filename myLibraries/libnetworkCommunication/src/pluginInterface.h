/*!
 * @brief Handles the plugin interface for the plugin
 *
 * @author hmarcks
 *
 * @addtogroup libNetworkCommunication
 *
 * @date 17/01/19
 */


#ifndef PROTOCOLDEVELOPER_PLUGININTERFACE_H
#define PROTOCOLDEVELOPER_PLUGININTERFACE_H

#include <pluginLoader/PluginLoaderCommon.h>

#include <I_communication.h>
#include <I_plugin.h>

namespace libNetworkCommunication
{

class pluginInterface
    : public PluginLoader::I_Plugin<Communication::I_communication>
{
public:
    /*!
     * @brief constructor
     */
    pluginInterface() = default;
    ~pluginInterface() override = default;
    /*!
     * @brief Returns the plugins name
     * @return The name of the plugin (as a const char*)
     */
    const char* getPluginName() final;
    /*!
     * @brief Returns the version of the plugin
     * @return The plugin version
     */
    const char* getPluginVersion() final;
    /*!
     * @brief Returns the plugin _type_
     * @return The the plugin is (as an enum)
     */
    PluginLoader::PLUGINTYPE_t getPluginType() final;
    /*!
     * @brief Returns a new plugin
     * @return A shared_ptr to the new object
     */
    std::shared_ptr<Communication::I_communication> createNewObject() final;
private:
};

/*!
 * @brief Returns a new plugin
 * @return A shared_ptr to the new object
 */
template<class IFType>
static std::shared_ptr<PluginLoader::I_Plugin<IFType>> createNewPlugin()
{
    return std::shared_ptr<PluginLoader::I_Plugin<Communication::I_communication>>();
}

} /* namespace libNetworkCommunication */

#endif /* PROTOCOLDEVELOPER_PLUGININTERFACE_H */

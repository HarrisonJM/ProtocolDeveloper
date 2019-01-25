/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 17/01/19
 */

#include "libNetworkCommunication.h"
#include <boost/dll/alias.hpp>

#include "pluginInterface.h"

namespace libNetworkCommunication
{
/*!
 * @brief Returns the plugins name
 * @return The name of the plugin (as a const char*)
 */
const char* pluginInterface::getPluginName()
{
    return "libNetworkCommunication-def";
}
/*!
 * @brief Returns the version of the plugin
 * @return The plugin version
 */
const char* pluginInterface::getPluginVersion()
{
    return "1.0";
}
/*!
 * @brief Returns the plugin _type_
 * @return The the plugin is (as an enum)
 */
PluginLoader::PLUGINTYPE_t pluginInterface::getPluginType()
{
    return PluginLoader::PLUGINTYPE_t::COMMUNICATION;
}
/*!
 * @brief creates a new NetworkCommuncation object and returns its address
 * @return A pointer to the new Communication object with it's default parameters
 */
std::shared_ptr<Communication::I_communication> pluginInterface::createNewObject()
{
    return std::make_shared<libNetworkCommunication>();
}
} /* namespace libNetworkCommunication */

/*!
 * @brief N.B. Uses alias exporting to load plugins
 * @{
 */
BOOST_DLL_ALIAS(
    libNetworkCommunication::createNewPlugin<Communication::I_communication>
    , createNewPlugin
               );
/*! @} */
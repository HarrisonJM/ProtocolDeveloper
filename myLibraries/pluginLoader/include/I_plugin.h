/*!
 * @brief Plugin baseclass that all plugins will derive from
 *
 * @author hmarcks
 *
 * @addtogroup PluginLoader
 *
 * @date 29/12/18
 */
#ifndef PROTOCOLDEVELOPER_I_PLUGIN_H
#define PROTOCOLDEVELOPER_I_PLUGIN_H

#include <memory>

#include "pluginLoader/PluginLoaderCommon.h"

namespace pluginLoader
{
/*!
 * @brief Top-level base class the plugin interfaces should derive from
 * @tparam IFType The interface type that we want to make a plugin for
 */
class I_Plugin
{
public:
    /*!
     * @brief Destructor
     */
    virtual ~I_Plugin() = default;
    /*!
     * @brief Returns the plugins name
     * @return The name of the plugin (as a const char*)
     */
    virtual const char* getPluginName() = 0;
    /*!
     * @brief Returns the version of the plugin
     * @return The plugin version
     */
    virtual const char* getPluginVersion() = 0;
    /*!
     * @brief Returns the plugin _type_
     * @return The the plugin is (as an enum)
     */
    virtual pluginLoader::PLUGINTYPE_t getPluginType() = 0;
};

} /* namespace pluginLoader */

#endif /* PROTOCOLDEVELOPER_I_PLUGIN_H */

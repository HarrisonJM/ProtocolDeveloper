/*!
 * @brief Where we store the plugin once it's initial functions have been loaded/mapped
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date 24/12/18
 */
#ifndef PROTOCOLDEVELOPER_PLUGINS_H
#define PROTOCOLDEVELOPER_PLUGINS_H

#include <functional>
#include <cstdarg>
#include <dlfcn.h>

#include "PluginLoaderCommon.h"

namespace pluginLoader
{
template<class TypeToReturn>
struct Plugin_S
{
public:
    Plugin_S() = default;
    ~Plugin_S()
    {
        dlclose(_libHandle);
    }

    std::function<const char*()> _getPluginName;
    std::function<const char*()> _getPluginVersion;
    std::function<PLUGINTYPE_t()> _getPluginType;
    std::shared_ptr<TypeToReturn> _newPlugin;

    void* _libHandle;
};

} /* namespace pluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINS_H */

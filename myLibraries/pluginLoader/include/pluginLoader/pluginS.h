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

#include "PluginLoaderCommon.h"

namespace PluginLoader
{
template<class TypeToReturn, typename ...Args>
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
    std::function<TypeToReturn()> _createObject;
    std::function<void(Args...)> _initialiseobject;

    void* _libHandle;
};
} /* namespace PluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINS_H */

/*!
 * @brief Defines an abstraction for the dllOpening using dlfcn
 *
 * @author hmarcks
 *
 * @addtogroup hmarcks
 *
 * @date 23/03/19
 */

#ifndef PROTOCOLDEVELOPER_DLLABSTRACT_H
#define PROTOCOLDEVELOPER_DLLABSTRACT_H

#include <string>
#include <memory>
#include <iostream>
#include <I_dllAbstract.h>
#include "pluginLoader_exception.h"

namespace pluginLoader
{
/*!
 * @brief Class that hides the ugly dlfcn functions
 * @tparam T The _type_ of the plugin we're returning
 */
template<typename T>
class dllAbstract : public I_dllAbstract<T>
{
public:
    /*!
     * @brief Constructor, comforms to RAiI
     * @param path The path to the dll
     */
    explicit dllAbstract(std::string const &path)
            :
            I_dllAbstract<T>(path)
            , _DLLHandle(nullptr)
    {
        _DLLHandle = dlopen(path.c_str()
                            , RTLD_LAZY);
        if (!_DLLHandle)
        {
            throw PluginHandleNullException(dlerror());
        }
    }
    /*!
     * @brief Destructor
     */
    ~dllAbstract()
    {
        dlclose(_DLLHandle);
    }
    /*!
     * @brief Returns a pointer to the factory function
     * @return A pointer to a function
     */
    std::shared_ptr<T> GetPluginFactory()
    {
        using allocClass = T *(*)();
        using deleteClass = void (*)(T *);

        auto createPlugin = reinterpret_cast<allocClass>(
                dlsym(_DLLHandle
                      , "createNewObject"));
        auto destroyPlugin = reinterpret_cast<deleteClass>(
                dlsym(_DLLHandle
                      , "destroyPlugin"));

        if (!createPlugin || !destroyPlugin)
        {
            dlclose(_DLLHandle);
            throw PluginFactoryNullException(dlerror());
        }

        return std::shared_ptr<T>(
                createPlugin()
                , [destroyPlugin](T *p)
                { destroyPlugin(p); });
    }
private:
    /*!
     * @brief A pointer to the handle used to open the SO
     */
    void *_DLLHandle;
};
} /* namespace pluginLoader */

#endif /* PROTOCOLDEVELOPER_DLLABSTRACT_H */

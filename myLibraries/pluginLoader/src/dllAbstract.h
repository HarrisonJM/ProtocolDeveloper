/*!
 * @brief Defines an abstraction for the dllOpening using dlfcn
 *
 * @author hmarcks
 *
 * @addtogroup pluginLoader
 * @{
 *
 * @date 23/03/19
 */

#ifndef PROTOCOLDEVELOPER_DLLABSTRACT_H
#define PROTOCOLDEVELOPER_DLLABSTRACT_H

#include <string>
#include <memory>
#include <iostream>

#include <I_dllAbstract.h>
#include <I_cDlfcn.h>
#include <freeFunctionsAndWrappers/cDlfcn.h>
#include "pluginLoader_exception.h"

namespace pluginLoader
{
/*!
 * @brief Class that hides the ugly dlfcn functions
 * @tparam T The _type_ of the plugin we're returning
 */
template<typename T>
class dllAbstract
    : public I_dllAbstract<T>
{
public:
    /*!
     * @brief Constructor, comforms to RAiI
     * @param path The path to the dll
     */
    explicit dllAbstract(std::string const& path)
        :
        I_dllAbstract<T>(path)
        , _DLLHandle(nullptr)
        , _dlfcnI((std::make_unique<cFunctions::cDlfcn>()))
    {
        _initClass(path);
    }
    /*!
    * @brief Constructor, comforms to RAiI
    * @param path The path to the dll
    * @param dlfcn_in
    */
    dllAbstract(std::string const& path
                , std::unique_ptr<cFunctions::I_cDlfcn> dlfcn_in)
        :
        I_dllAbstract<T>(path)
        , _DLLHandle(nullptr)
        , _dlfcnI(std::move(dlfcn_in))
    {
        _initClass(path);
    }
    /*!
     * @brief Destructor
     */
    ~dllAbstract()
    {
        _dlfcnI->dlcloseHandle(_DLLHandle);
    }
    /*!
     * @brief Returns a pointer to the factory function
     * @return A pointer to a function
     */
    std::shared_ptr<T> GetPluginFactory()
    {
        using allocClass = T* (*)();
        using deleteClass = void (*)(T*);

        auto createPlugin = reinterpret_cast<allocClass>(_dlfcnI->dlsymbol
            (_DLLHandle
                  , "createNewObject"));
        auto destroyPlugin = reinterpret_cast<deleteClass>(
            _dlfcnI->dlsymbol(_DLLHandle
                  , "destroyPlugin"));

        if (!createPlugin || !destroyPlugin)
        {
            _dlfcnI->dlcloseHandle(_DLLHandle);
            throw PluginFactoryNullException(_dlfcnI->dlerrorStr());
        }

        return std::shared_ptr<T>(
            createPlugin()
            , [destroyPlugin](T* p)
            { destroyPlugin(p); });
    }
private:
    /*!
     * @brief inits the class
     */
    void _initClass(std::string const& path)
    {
        _DLLHandle = _dlfcnI->dlopenHandle(path.c_str()
                            , 0x00001); /* Lazy binding */
        if (!_DLLHandle)
        {
            throw PluginHandleNullException(_dlfcnI->dlerrorStr());
        }
    }
    /*!
     * @brief A pointer to the handle used to open the SO
     */
    void* _DLLHandle;
    /*!
     * @brief The implementation we wish to use for the dynamic loading
     */
    std::unique_ptr<cFunctions::I_cDlfcn> _dlfcnI;
};
} /* namespace pluginLoader */
/*! @} */
#endif /* PROTOCOLDEVELOPER_DLLABSTRACT_H */

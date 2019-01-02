/*!
 * @brief ProtocolPluginLoader
 *
 * See header description
 *
 * MUST ADD INGROUP
 *
 * @date March 2018
 */
#include "pluginLoader/ProtocolPluginLoader.h"

#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

namespace PluginLoader
{
    //! @todo: expand
    //! @todo: Needs to loop over an entire directory
    /*!
     * @brief default_constructor
     *
     * loads a plugin
     */
    ProtocolPluginHandler::ProtocolPluginHandler()
    {
        // Loads a given plugin
        //! @todo: pass in the path
        lib_handle = dlopen("plugin/plug.so"
                            , RTLD_LAZY | RTLD_GLOBAL);
        if (!lib_handle)
        {
            fprintf(stderr, "%s\n", dlerror());
            exit(1);
        }

        create = (I_ProtocolInterface *(*)()) dlsym(lib_handle, "create_obj");

        destroy = (void (*)(I_ProtocolInterface*)) dlsym(lib_handle, "destroy_obj");

        if ((errorMess = dlerror()) != nullptr)
        {
            fprintf(stderr, "%s\n", errorMess);
            exit(1);
        }
    }

/*!
 * @brief destructor
 */
    ProtocolPluginHandler::~ProtocolPluginHandler()
    {
        delete (if_f);
        dlclose(lib_handle);
    }

    /*!
     * @brief getIF
     *
     * Our main factory. Returns a pointer to an interface that we can use
     * To access anything generated in our protocol library
     *
     * @return A pointer to the interface we'll be using
     */
    I_ProtocolInterface *ProtocolPluginHandler::getIF()
    {
        this->if_f = (I_ProtocolInterface*) create();

        return if_f;
    }
}
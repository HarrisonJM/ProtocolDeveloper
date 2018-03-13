/*!
 * @brief ProtocolPluginLoader
 *
 * See header description
 *
 * MUST ADD INGROUP
 *
 * @date March 2018
 */
#include "ProtocolPluginLoader.h"

#include <stdio.h>
#include <stdlib.h>
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
        lib_handle = dlopen("plugin/plug.so", RTLD_LAZY);
        if (!lib_handle)
        {
            fprintf(stderr, "%s\n", dlerror());
            exit(1);
        }

        create = (ProtocolInterface *(*)()) dlsym(lib_handle, "create_obj");

        destroy = (void (*)(ProtocolInterface*)) dlsym(lib_handle, "destroy_obj");

        if ((errorMess = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", errorMess);
            exit(1);
        }
    }

    /*
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
    ProtocolInterface *ProtocolPluginHandler::getIF()
    {
        this->if_f = (ProtocolInterface*) create();

        return if_f;
    }
}
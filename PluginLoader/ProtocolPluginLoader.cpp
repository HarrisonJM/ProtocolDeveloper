#include "ProtocolPluginLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

namespace PluginLoader
{
    //TODO: expand
    //TODO: Needs to loop over an entire directory
    ProtocolPluginHandler::ProtocolPluginHandler()
    {
        // Loads a given plugin
        // TODO: pass in the path
        lib_handle = dlopen("plugin/plug.so", RTLD_LAZY);
        if (!lib_handle)
        {
            fprintf(stderr, "%s\n", dlerror());
            exit(1);
        }

        create = (ProtocolInterface<std::string, std::string> *(*)()) dlsym(lib_handle, "create_obj");

        destroy = (void (*)(ProtocolInterface<std::string, std::string> *)) dlsym(lib_handle, "destroy_obj");

        if ((errorMess = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", errorMess);
            exit(1);
        }
    }

    ProtocolPluginHandler::~ProtocolPluginHandler()
    {
        delete (if_f);
        dlclose(lib_handle);
    }

    // Our main factory. Returns a pointer to an interface that we can use
    // To access anything generated in our protocol library
    ProtocolInterface<std::string, std::string> *ProtocolPluginHandler::getIF()
    {
        this->if_f = (ProtocolInterface<std::string, std::string> *) create();

        return if_f;
    }
}
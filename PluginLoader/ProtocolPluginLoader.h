//
// Created by hmarcks on 24/02/18.
//

#include "ProtocolInterface.h"
#include "PluginLoaderInterface.h"

#ifndef PROTOCOLDEVELOPER_PLUGINHANDLER_H
#define PROTOCOLDEVELOPER_PLUGINHANDLER_H

//TODO: This needs to be made into a more factory pattern
//TODO: so that different parts of the program may all haev plugins
//TODO: loaded using only a single class
namespace PluginLoader
{
//Loads our DLL
    class ProtocolPluginHandler : //public ProtocolInterface,
                                  public PluginLoaderInterface
    {
    public:
        ProtocolPluginHandler();
        ~ProtocolPluginHandler();

        ProtocolInterface *getIF();

    private:
        void *lib_handle;
        ProtocolInterface *(*create)();
        void (*destroy)(ProtocolInterface *);

        int x;
        char *errorMess;

        ProtocolInterface *if_f;

    };
}

#endif //PROTOCOLDEVELOPER_PLUGINHANDLER_H

/*!
 * @brief ProtocolPluginLoader
 *
 * Will likely be refactored so that it only loads third party libraries
 * Current purpose is to at some staeg load different protocols in
 *
 * MUST ADD INGROUP
 *
 * @date March 2018
 */
#include "I_protocolInterface.h"
#include "I_PluginLoader.h"

#include <string>

#ifndef PROTOCOLDEVELOPER_PLUGINHANDLER_H
#define PROTOCOLDEVELOPER_PLUGINHANDLER_H

//! @todo: This needs to be made into a more factory pattern
//! @todo: so that different parts of the program may all haev plugins
//! @todo: loaded using only a single class
namespace PluginLoader
{
    /*!
     * @brief Loads our DLL
     *
     * Will be rethought and replaced with BOOST::dll
     */
    class ProtocolPluginHandler : public I_PluginLoader
    {
    public:
        //! Constructor
        ProtocolPluginHandler();
        //! Destructor
        ~ProtocolPluginHandler();
        //! Returns an interface
        Protocol::I_ProtocolInterface *getIF();

    private:
        //! the libaray handle
        void *lib_handle;
        //! creates and returns a new interface
        Protocol::I_ProtocolInterface *(*create)();
        //! destroy interface
        void (*destroy)(Protocol::I_ProtocolInterface*);
        //! x
        int x;
        //! errorMessage from dll loading
        char *errorMess;

        Protocol::I_ProtocolInterface* if_f;
    };
}

#endif //PROTOCOLDEVELOPER_PLUGINHANDLER_H

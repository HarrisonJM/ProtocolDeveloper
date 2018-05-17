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
#include "ProtocolInterface.h"
#include "PluginLoaderInterface.h"

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
    class ProtocolPluginHandler : public PluginLoaderInterface
    {
    public:
        //! Constructor
        ProtocolPluginHandler();
        //! Destructor
        ~ProtocolPluginHandler();
        //! Returns an interface
        ProtocolInterface *getIF();

    private:
        //! the libaray handle
        void *lib_handle;
        //! creates and returns a new interface
        ProtocolInterface *(*create)();
        //! destroy interface
        void (*destroy)(ProtocolInterface*);

        //! x
        int x;
        //! errorMessage from dll loading
        char *errorMess;

        ProtocolInterface*if_f;
    };
}

#endif //PROTOCOLDEVELOPER_PLUGINHANDLER_H

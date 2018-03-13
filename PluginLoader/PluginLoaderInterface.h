/*!
 * @brief The pluginHandler Interface
 *
 * This pluginHandler will be used to load various third party libraries dynamically
 *
 * MUST ADD INGROUP
 *
 * @date March 2018
 */

#ifndef PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H
#define PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H

namespace PluginLoader
{
    class PluginLoaderInterface
    {
    public:
        //! @todo: MAKE GENERIC, SOMEHOW
        virtual ~PluginLoaderInterface();
    private:

    };
}
#endif //PROTOCOLDEVELOPER_PLUGINHANDLERINTERFACE_H

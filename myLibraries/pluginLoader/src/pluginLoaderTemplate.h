/*!
 * @brief Class specifically for loading the communications plugins
 *
 * The implementations are below the class. The source file exclusively
 * contains specializations for the templates according to the plugin type
 * being loaded
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date 24/12/18
 */
#ifndef PROTOCOLDEVELOPER_PLUGINLOADERCOMMS_H
#define PROTOCOLDEVELOPER_PLUGINLOADERCOMMS_H

#include <map>
#include <string>
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <cstdlib>
#include <cxxabi.h>

#include <I_communication.h>
#include <I_protocolInterface.h>

#include <pluginLoader/PluginLoaderCommon.h>
#include <filesystem>
#include "pluginLoader/pluginS.h"
#include "dllAbstract.h"
#include "pluginLoader_exception.h"

namespace PluginLoader
{
/*!
 * @brief Class that loads the plugins we want for the desired area
 * @tparam TpluginType The plugin we wish to load
 *
 * The template parameter can be one of:
 * Communication::I_comunication
 * Protocol::I_protocolInterface
 * <>
 *
 * @todo the other interfaces
 */
template<class TpluginType>
class PluginLoaderTemplate
{
public:
    /*!
     * @brief Constructor
     * @param _prefix The top level directory where plugins are stored (i.e. "/opt/ProtDev/Plugins")
     * @param _qualifier The folder the plugins are stored in (i.e. "comms" or "")
     */
    PluginLoaderTemplate(std::string const& prefix
                         , std::string const& qualifier
                         , sharedMap_t<TpluginType>& plugins);
    /*!
     * @brief Default Destructor
     */
    ~PluginLoaderTemplate() = default;
    /*!
     * @brief Scans for plugins in location pointed to by _fullPath
     */
    void ScanForPlugins();
    /*!
     * @brief Scans for plugins in the provided location
     * @param newDir The directory where it should search for plugins
     */
    void ScanForPlugins(std::string newDir);
    /*!
     * @brief Gets the held plugin list
     * @return a sharedMap_t type
     */
    sharedMap_t<TpluginType> getPlugins();
private:
    /*! @brief The full default path of the where the comms plugins are*/
    std::string _fullPath;
    /*! @brief Communication Plugins */
    sharedMap_t<TpluginType>& _plugins;
    /*!
     * @brief Compares the passed in type and verifies it against the one we want
     * @param pt1 The plugin type we'd like to compare
     * @return true on match, otherwise false (Always false if not incorrect template used)
     */
    bool _CheckCorrectType(PLUGINTYPE_t pt1);
};
/////////////////////////// Implementations below /////////////////////////////

/*!
 * @brief Constructor
 * @param _prefix The top level directory where plugins are stored (i.e. "/opt/ProtDev/Plugins")
 * @param _qualifier The folder the plugins are stored in (i.e. "comms" or "")
 */
template<class TpluginType>
PluginLoaderTemplate<TpluginType>::PluginLoaderTemplate(std::string const& prefix
                                                        , std::string const& qualifier
                                                        , sharedMap_t<TpluginType>& plugins)
    : _fullPath(prefix + "/" + qualifier)
      , _plugins(plugins)
{
}
/*!
 * @brief Scans for plugins in location pointed to by _fullPath
 */
template<class TpluginType>
void PluginLoaderTemplate<TpluginType>::ScanForPlugins()
{
    ScanForPlugins(_fullPath);
}
/*!
 * @brief Scans for plugins in the provided location
 * @param newDir The directory where it should search for plugins
 */
template<class TpluginType>
void PluginLoaderTemplate<TpluginType>::ScanForPlugins(std::string newDir)
{
    if (!std::filesystem::is_directory(newDir))
    {
        //! @todo Not a directory. throw
    }
    else
    {
        for (const auto& file : std::filesystem::directory_iterator(newDir))
        {
            /* Currently pointed to file is not a directory */
            if (!std::filesystem::is_directory(file))
            {
                try
                {
                    dllAbstract<TpluginType> da(std::filesystem::path(file).string());
                    auto foo = da.GetPluginFactory();

                    if (_CheckCorrectType(foo->getPluginType()))
                    {
                        _plugins.insert(std::pair<std::string, decltype(foo)>
                                            (foo->getPluginName()
                                             , foo));
                    }
                }
                catch (PluginException& e)
                {
                    // Incorrect file type in directory or smth
                    std::cout << e.what() << std::endl;
                    continue;
                }
            }
        }
    }
}
/*!
 * @brief Gets the held plugin list
 * @return a sharedMap_t type
 */
template<class TpluginType>
sharedMap_t<TpluginType> PluginLoaderTemplate<TpluginType>::getPlugins()
{
    return _plugins;
}
/*!
 * @brief Checks a correct type, used for tempalte specialization
 * @tparam TpluginType The plugin type (interface) that we're using
 * @param pt1 The plugin type we'd like to compare
 * @return Always false if not specialised
 */
template<class TpluginType>
bool PluginLoaderTemplate<TpluginType>::_CheckCorrectType(PLUGINTYPE_t pt1)
{
    return false;
}

/* FORWARD DECLARATIONS/PROTOTYPES */

/*!
 * @brief Specialised template method prototype specifically for finding I_Communication plugins
 * @param pt1 The plugin type we'ed like to compare
 * @return true on match, otherwise false
 */
template<>
bool PluginLoaderTemplate<Communication::I_communication>::_CheckCorrectType(PLUGINTYPE_t pt1);
/*!
 * @brief Specialised template method prototype specifically for finding I_ProtocolInterface plugins
 * @param pt1 The plugin type we'ed like to compare
 * @return true on match, otherwise false
 */
template<>
bool PluginLoaderTemplate<Protocol::I_protocolInterface>::_CheckCorrectType(PLUGINTYPE_t pt1);

//! @todo More specializations

} /* namespace PluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINLOADERCOMMS_H */

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

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>

#include <I_communication.h>
#include <pluginLoader/PluginLoaderCommon.h>
#include "pluginLoader/pluginS.h"

namespace PluginLoader
{
/*!
 * @brief Class that loads the plugins we want for the desired area
 * @tparam TpluginType The plugin we wish to load
 *
 * The template parameter can be one of:
 * Communication::I_Coomunication
 * <>
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
    PluginLoaderTemplate(std::string const &prefix
                         , std::string const &qualifier
                         , sharedMap_t<TpluginType> &pluginsRef);
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
    sharedMap_t<TpluginType> &_plugins;
    /*!
     * @brief Compares the passed in type and verifies it against the one we want
     * @param pt1 The plugin type we'd like to compare
     * @return true on match, otherwise false (Always false if not incorrect tempalte used)
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
PluginLoaderTemplate<TpluginType>::PluginLoaderTemplate(std::string const &prefix
                                                        , std::string const &qualifier
                                                        , sharedMap_t<TpluginType> &pluginsRef)
    : _fullPath(prefix + "/" + qualifier)
      , _plugins(pluginsRef)
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
    if (!boost::filesystem::is_directory(newDir))
    {
        // Not a directory. Log or throw?
    }
    else
    {
        for (const auto &file : boost::filesystem::directory_iterator(newDir))
        {
            // Currently pointed to file is a directory
            if (boost::filesystem::is_directory(newDir))
            {
                // Get the alias
                auto tempPtr = boost::dll::import_alias<TpluginType>(file
                                                                     , "NetworkCommunication"
                                                                     , boost::dll::load_mode::append_decorations);
                // Make it a std::shared_ptr
                std::shared_ptr<TpluginType> commsPluginTemp;
                commsPluginTemp = make_shared_ptr<TpluginType>(tempPtr);

                // Add the plugin to our map
                if (commsPluginTemp->getPluginType() == PLUGINTYPE_t::COMMUNICATION)
                    _plugins->operator[](static_cast<int>(_plugins->size())) = commsPluginTemp;
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
/*!
 * @brief Specialised template method specifically for finding I_Communication plugins
 * @param pt1 The plugin type we'ed like to compare
 * @return true on match, otherwise false
 */
template<>
bool PluginLoaderTemplate<Communication::I_communication>::_CheckCorrectType(PLUGINTYPE_t pt1);

//! @todo More specializations

} /* namespace PluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINLOADERCOMMS_H */

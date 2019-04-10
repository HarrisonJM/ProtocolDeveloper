/*!
 * @brief Class specifically for loading the communications plugins
 *
 * The implementations are below the class. The source file exclusively
 * contains specializations for the templates according to the plugin type
 * being loaded
 *
 * @author hmarcks
 *
 * @addtogroup pluginLoader
 * @{
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
#include <magic.h>
#include <filesystem>

#include <I_communication.h>
#include <I_protocolInterface.h>
#include <I_pluginLoaderTemplate.h>

#include <pluginLoader/PluginLoaderCommon.h>
#include <logger/loggerUtility.h>
#include <logger/LogHandler.h>
#include "dllAbstract.h"
#include "pluginLoader_exception.h"

namespace pluginLoader
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
    : public I_PluginLoaderTemplate<TpluginType>
{
public:
    /*!
     * @brief Constructor
     * @param prefix The top level directory where plugins are stored (i.e. "/opt/ProtDev/Plugins")
     * @param qualifier The folder the plugins are stored in (i.e. "comms" or "")
     * @param plugins Where to store the plugins
     * @param loggerID The ID the of the logger we're using
     */
    PluginLoaderTemplate(std::string const& prefix
                         , std::string const& qualifier
                         , sharedMap_t<TpluginType>& plugins
                         , long loggerID);
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
    /*! @brief The ID of the logger we're using */
    const long _loggerID;
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
 * @param prefix The top level directory where plugins are stored (i.e. "/opt/ProtDev/Plugins")
 * @param qualifier The folder the plugins are stored in (i.e. "comms" or "")
 * @param plugins Where to store the plugins
 * @param loggerID The ID the of the logger we're using
 */
template<class TpluginType>
PluginLoaderTemplate<TpluginType>::PluginLoaderTemplate(std::string const& prefix
                                                        , std::string const& qualifier
                                                        , sharedMap_t<TpluginType>& plugins
                                                        , const long loggerID)
    : _loggerID(loggerID)
      , _fullPath(prefix + "/" + qualifier)
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
        char str[] = "";
        throw PluginSuppliedDirectoryIsNotADirectory(str);
    }
    else
    {
        auto handle = ::magic_open(MAGIC_NONE | MAGIC_COMPRESS);
        ::magic_load(handle
                     , nullptr);

        for (const auto& file : std::filesystem::directory_iterator(newDir))
        {
            /* Currently pointed to file is not a directory */
            if (!std::filesystem::is_directory(file))
            {
                /* Check the file for its magic number to confirm it is indeed a shared object*/
                auto type = ::magic_file(handle
                                         , file.path().native().c_str());
                if (std::string(type).find("shared object") != std::string::npos)
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
                        // Couldn't load file
                        LOGMESSAGE(e.what()
                                   , logger::logLevel::ERROR);
                        continue;
                    }
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

} /* namespace pluginLoader */
/*! @} */
#endif /* PROTOCOLDEVELOPER_PLUGINLOADERCOMMS_H */

/*!
 * @brief interface for th epluginloadertempalte class
 * @author Harrison Marcks
 * @date 8/4/19
 * @addtogroup pluginLoader
 * @{
 * @addtogroup interfaces
 * @{
 */

#ifndef __PROTOCOLDEVELOPER_I_PLUGINLOADERTEMPLATE_H__
#define __PROTOCOLDEVELOPER_I_PLUGINLOADERTEMPLATE_H__

#include <string>
#include <pluginLoader/PluginLoaderCommon.h>

namespace pluginLoader
{
template<class TpluginType>
class I_PluginLoaderTemplate
{
public:
    /*!
     * @brief Default Destructor
     */
    ~I_PluginLoaderTemplate() = default;
    /*!
     * @brief Scans for plugins in location pointed to by _fullPath
     */
    virtual void ScanForPlugins() = 0;
    /*!
     * @brief Scans for plugins in the provided location
     * @param newDir The directory where it should search for plugins
     */
    virtual void ScanForPlugins(std::string newDir) = 0;
    /*!
     * @brief Gets the held plugin list
     * @return a sharedMap_t type
     */
    virtual sharedMap_t<TpluginType> getPlugins() = 0;
};
} /* namespace pluginLoader */
/*! @} @} */
#endif //__PROTOCOLDEVELOPER_I_PLUGINLOADERTEMPLATE_H__

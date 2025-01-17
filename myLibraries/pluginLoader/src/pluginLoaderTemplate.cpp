/*!
 * @brief Required source file implementations of specific template specializations
 *
 * @author hmarcks
 *
 * @addtogroup PluginLoader
 * @{
 * @date 30/12/18
 * @todo More specializations
 */
#include "pluginLoaderTemplate.h"

namespace pluginLoader
{
/*!
 * @brief Specialised template method specifically for finding I_Communication plugins
 * @param pt1 The plugin type we'ed like to compare
 * @return true on match, otherwise false
 */
template<>
bool PluginLoaderTemplate<Communication::I_communication>::_CheckCorrectType(PLUGINTYPE_t pt1)
{
    return (PLUGINTYPE_t::COMMUNICATION == pt1);
}
/*!
 * @brief Specialised template method prototype specifically for finding I_ProtocolInterface plugins
 * @param pt1 The plugin type we'ed like to compare
 * @return true on match, otherwise false
 */
template<>
bool PluginLoaderTemplate<Protocol::I_protocolInterface>::_CheckCorrectType(PLUGINTYPE_t pt1)
{
    return (PLUGINTYPE_t::PROTOCOL == pt1);
}
}

/*! @} */
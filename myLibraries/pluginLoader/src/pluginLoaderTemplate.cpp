/*!
 * @brief Required source file implementations of specific template specializations
 *
 * @author hmarcks
 *
 * @addtogroup PluginLoader
 *
 * @date 30/12/18
 * @todo More specializations
 */

#include "pluginLoaderTemplate.h"

namespace PluginLoader
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
}
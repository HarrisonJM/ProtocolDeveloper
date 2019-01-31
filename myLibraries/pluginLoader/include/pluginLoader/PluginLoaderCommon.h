/*!
 * @brief Common definitions used in the plugin loader
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date 24/12/18
 *
 * @todo Move the ptr functions to their own file or smth
 * @todo Move the shareMap_t to its own file
 */
#ifndef PROTOCOLDEVELOPER_PLUGINLOADERCOMMON_H
#define PROTOCOLDEVELOPER_PLUGINLOADERCOMMON_H

#include <memory>
#include <boost/shared_ptr.hpp>

#include <functional>
#include <map>

#include "../I_plugin.h"

namespace PluginLoader
{
/*!
 * @brief Handles conversions between std and boost shared ptrs
 * https://stackoverflow.com/questions/12314967/cohabitation-of-boostshared-ptr-and-stdshared-ptr
 * @{
 */
/*!
 * @brief Makes a std::shared pointer usable by the boost library. Don't use with weak_ptr's
 * @tparam T The type that the shared ptr holds
 * @param ptr A reference to the pointer we wish to convert
 * @return A copy of the pointer in the form we actually want
 */
template<typename T>
boost::shared_ptr<T> make_shared_ptr(std::shared_ptr<T>& ptr)
{
    return boost::shared_ptr<T>(ptr.get()
                                , [ptr](T*) mutable
        { ptr.reset(); });
}
/*!
 * @brief Makes a boost::shared_ptr usable by the std library. Don't use with weak_ptr's
 * @tparam T The type that the shared ptr holds
 * @param ptr A reference to the pointer we wish to convert
 * @return A copy of the pointer in the form we actually want
 */
template<typename T>
std::shared_ptr<T> make_shared_ptr(boost::shared_ptr<T>& ptr)
{
    return std::shared_ptr<T>(ptr.get()
                              , [ptr](T*) mutable
        { ptr.reset(); }
                             );
}
/*!@}*/
/*!
 * @brief The different types that the plugin can be
 * @{
 */
enum PLUGINTYPE_t
    : short
{
    COMMUNICATION, /*! < Used for communication plugins */
    PROTOCOL, /*! < Used for protocol plugins */
    THREAD, /*! < Used for thread handlers */
    TESTCASE /*! < Used for testcase plugins */

};
/*!}@*/

/*!
 * @brief A shared ptr to a map of strings and sharedptr's containing plugin interfaces
 */
template<class TypeToUse>
using sharedMap_t = std::shared_ptr<std::map<std::string, std::shared_ptr<PluginLoader::I_Plugin<TypeToUse> > > >; // ptr, pair

} /* namespace PluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINLOADERCOMMON_H */

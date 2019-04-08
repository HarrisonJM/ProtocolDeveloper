/*!
 * @brief Interface for the dllAbstract class
 * @author Harrison Marcks
 * @date 8/4/19
 */

#ifndef __PROTOCOLDEVELOPER_I_DLLABSTRACT_H__
#define __PROTOCOLDEVELOPER_I_DLLABSTRACT_H__

#include <string>
#include <memory>

namespace pluginLoader
{
/*!
  * @brief Interface for the class that hides the ugly dlfcn functions
  * @tparam T The _type_ of the plugin we're returning
  */
template<typename T>
class I_dllAbstract
{
public:
    /*!
     * @brief Constructor, conforms to RAiI
     * @param path The path to the dll
     */
    explicit I_dllAbstract(std::string const& path){};
    /*!
     * @brief Destructor
     */
    ~I_dllAbstract() = default;
    /*!
     * @brief Returns a pointer to the factory function
     * @return A pointer to a function
     */
    virtual std::shared_ptr<T> GetPluginFactory() = 0;
};
} /* namespace pluginLoader */

#endif //__PROTOCOLDEVELOPER_I_DLLABSTRACT_H__

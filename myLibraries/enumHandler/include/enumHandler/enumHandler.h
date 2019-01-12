/*!
 * @brief Handles Enum Conversion
 *
 * Registers a series of enum values and their string equivalents
 *
 * @addtogroup Utility
 *
 * @date 10/08/18
 */

#ifndef PROTOCOLDEVELOPER_ENUMHANDLER_H
#define PROTOCOLDEVELOPER_ENUMHANDLER_H

#include <map>

namespace Utility
{
/*!
 * @brief Maps enums
 * @tparam K The key by which we want to look up values
 * @tparam V What we want to return
 */
template <class K, class V>
class EnumHandler
{
public:
    /*!
     * @brief Default Constructor
     */
    EnumHandler() = default;
    /*!
     * @brief Default Destructor
     */
    ~EnumHandler() = default;
    /*!
     * @brief Registers an Enum to the internal map
     * @param key The key for the value
     * @param value The value described by the key
     */
    void RegisterEnum(K key, V value)
    {
        _keyPairs[key] = value;
    }
    /*!
     * @brief Looks up a value based on the key
     * @param key The key for the value we wish to look up
     * @return A copy of the stored value
     */
    V getValue(K key)
    {
        auto it = _keyPairs.find(key);
        return it == _keyPairs.end() ? static_cast<V>(0) : it->second;
    }

private:
    /*!
     * @brief Stores the key/value pairs
     */
    std::map<K, V> _keyPairs;
};
} /* namespace Utility */

#endif //PROTOCOLDEVELOPER_ENUMHANDLER_H

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

template <class K, class V>
class EnumHandler
{
public:
    EnumHandler() = default;
    ~EnumHandler() = default;

    void RegisterEnum(K key, V value)
    {
        _keyPairs[key] = value;
    }

    V getValue(K key)
    {
        auto it = _keyPairs.find(key);
        return it == _keyPairs.end() ? "Out of range" : it->second;
    }

private:
    std::map<K, V> _keyPairs;

};
} /* namespace Utility */

#endif //PROTOCOLDEVELOPER_ENUMHANDLER_H

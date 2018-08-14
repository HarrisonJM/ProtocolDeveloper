/*!
 * @brief Handles Enum Conversion
 *
 * Registers a series of enum values and their string equivalents
 *
 * @date 10/08/18
 */

#ifndef PROTOCOLDEVELOPER_ENUMHANDLER_H
#define PROTOCOLDEVELOPER_ENUMHANDLER_H

#include <map>

namespace Utility {

template <class K, class V>
class EnumHandler
{
public:
    EnumHandler() = defaut
    {

    }

    ~EnumHandler()
    {

    }

    void RegisterEnum(K key, V value)
    {
        keyPairs[key] = value;
    }

    V getValue(K key)
    {
        auto it = keyPairs.find(key);
        return it == keyPairs.end() ? "Out of range" : it->second;
    }

private:
    std::map<K, V> keyPairs;

};

} /* namespace utility */

#endif //PROTOCOLDEVELOPER_ENUMHANDLER_H

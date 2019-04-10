/*!
 * @brief Mocks for the dllabstract class
 * @author hmarcks
 * @date 8/4/19
 * @addtogroup mockLibrary
 * @{
 */
#ifndef __PROTOCOLDEVELOPER_DLLABSTRACTMOCKS_H__
#define __PROTOCOLDEVELOPER_DLLABSTRACTMOCKS_H__

#include <gmock/gmock.h>
#include <I_dllAbstract.h>

namespace pluginLoader
{
template<typename T>
class dllAbstractMocks
    : public I_dllAbstract<T>
{
    explicit dllAbstractMocks(std::string const& path) : I_dllAbstract<T>(path)
    {}
    MOCK_METHOD0_T(GetPluginFactory
                   , std::shared_ptr<T>(void));
};
}
/*! @} */
#endif //__PROTOCOLDEVELOPER_DLLABSTRACTMOCKS_H__

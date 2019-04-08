/*!
 * @brief Exceptions for the pluginloader class
 *
 * @author hmarcks
 *
 * @addtogroup Plugin Loader
 *
 * @date 23/03/19
 */

#ifndef PROTOCOLDEVELOPER_PLUGINLOADER_EXCEPTION_H
#define PROTOCOLDEVELOPER_PLUGINLOADER_EXCEPTION_H

#include <exception>
#include <cstring>
#include <utility/extraExceptionBase.h>

namespace pluginLoader
{
class PluginException
    : public utility::extraExceptionBase
{
public:
    PluginException(char* dlError)
        : utility::extraExceptionBase(dlError)
    {
    }
    virtual const char* what() override
    {
        return "PluginException";
    }
};
/*!
 * @brief The plugin handle has returned NULL (The plugin cannot be opened)
 */
class PluginHandleNullException
    : public PluginException
{
public:
    explicit PluginHandleNullException(char* dlError)
        : PluginException(dlError)
    {

    }
    const char* what() override
    {
        return _BuildError("Returned DLL Handle is NULL. ERROR: ");
    }
};
/*!
 * @brief The plugin has returned NULL when finding the factory symbol
 */
class PluginFactoryNullException
    : public PluginException
{
public:
    explicit PluginFactoryNullException(char* dlError)
        : PluginException(dlError)
    {

    }
    const char* what() override
    {
        return _BuildError("Returned DLL factory is NULL.");
    }
};
/*!
 * @brief The plugin has returned NULL when finding the factory symbol
 */
class PluginSuppliedDirectoryIsNotADirectory
    : public PluginException
{
public:
    explicit PluginSuppliedDirectoryIsNotADirectory(char* dlError)
        : PluginException(dlError)
    {

    }
    const char* what() override
    {
        return _BuildError("Plugin Supplied Directory Is Not A Directory.");
    }
};

} /* namespace pluginLoader */

#endif /* PROTOCOLDEVELOPER_PLUGINLOADER_EXCEPTION_H */

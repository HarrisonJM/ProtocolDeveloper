/*!
 * @brief Exceptions for the service lib class
 *
 * @author hmarcks
 * @date 14/04/19
 * @addtogroup serviceLib
 * @{
 * @addtogroup exceptions
 * @{
 */
#include <exception>
#include <utility/extraExceptionBase.h>
#include <cerrno>

#ifndef __PROTOCOLDEVELOPER_SERVICELIB_EXCEPTIONS_H__
#define __PROTOCOLDEVELOPER_SERVICELIB_EXCEPTIONS_H__

namespace serviceLib
{
class serviceLib_exception
    : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "The daemoniser has died on the first hurdle. :(";
    }
};
class serviceLib_exception_getrlimit : public utility::extraExceptionBase
{
public:
    explicit serviceLib_exception_getrlimit()
    : extraExceptionBase(strerror(errno))
    {}
    virtual const char* what() override
    {
        return _BuildError("rlimit error: ");
    }
};
class serviceLib_exception_pidlessthan0 : public utility::extraExceptionBase
{
public:
    explicit serviceLib_exception_pidlessthan0()
        : extraExceptionBase(strerror(errno))
    {}
    virtual const char* what() override
    {
        return _BuildError("pidlessthan 0 error: ");
    }
};
class serviceLib_exception_ignoreSIGHUP: public utility::extraExceptionBase
{
public:
    explicit serviceLib_exception_ignoreSIGHUP()
        : extraExceptionBase(strerror(errno))
    {}
    virtual const char* what() override
    {
        return _BuildError("Can't ignore SIGHUP error: ");
    }
};
class serviceLib_exception_cdRootDir: public utility::extraExceptionBase
{
public:
    explicit serviceLib_exception_cdRootDir()
        : extraExceptionBase(strerror(errno))
    {}
    virtual const char* what() override
    {
        return _BuildError("Can't change to root dir: ");
    }
};
class serviceLib_exception_unexpectedFD: public utility::extraExceptionBase
{
public:
    explicit serviceLib_exception_unexpectedFD()
        : extraExceptionBase(strerror(errno))
    {}
    virtual const char* what() override
    {
        return _BuildError("Unexpected FDs: ");
    }
};
} /* namespace serviceLib */

/*! @} @} */
#endif /* __PROTOCOLDEVELOPER_SERVICELIB_EXCEPTIONS_H__ */

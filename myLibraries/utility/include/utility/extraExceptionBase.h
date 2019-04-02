/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 23/03/19
 */


#ifndef PROTOCOLDEVELOPER_EXTRAEXCEPTIONBASE_H
#define PROTOCOLDEVELOPER_EXTRAEXCEPTIONBASE_H

#include <cstring>

namespace utility
{
/*!
 * @brief Base analyser exception class
 */
class extraExceptionBaseLength
    : public std::exception
{
public:
    explicit extraExceptionBaseLength(const char* info
                                      , size_t length)
        : _info(info)
          , _length(length)
    {
    }
    virtual const char* what()
    {
        return "ProtDev Exception";
    }
    ~extraExceptionBaseLength()
    {
    }
protected:

    const char* _BuildError(const char* errorMessage)
    {
        if (!errorMessage)
        {
            errorMessage = _bkp;
        }
        std::strcat(_error
                    , errorMessage);
        std::strncat(_error
                     , _info
                     , _length);
        return _error;
    }
private:
    const char* _info;
    char _bkp[128];
    char _error[16384];
    const size_t _length;
};
/*!
 * @brief PluginException base class for handling the dlError ro any other extras
 */
class extraExceptionBase
    : public extraExceptionBaseLength
{
public:
    /*!
     * @brief Constrcutor
     * @param dlError The dlerror() return (or other string)
     */
    explicit extraExceptionBase(const char* dlError)
        : extraExceptionBaseLength(dlError
                                   , [](const char* dlError_l) -> size_t
        {
            if (!dlError_l)
                return 0;
            return strlen(dlError_l);
        }(dlError))
    {
    }
    virtual const char* what() override
    {
        return "ProtDev Exception";
    }
    ~extraExceptionBase() override = default;
};
} /* namespace utility */

#endif /* PROTOCOLDEVELOPER_EXTRAEXCEPTIONBASE_H */

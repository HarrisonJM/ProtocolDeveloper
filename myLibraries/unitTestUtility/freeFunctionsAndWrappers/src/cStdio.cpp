/*!
 * @brief Wrapper implementation for normal c functions
 *
 * @author hmarcks
 *
 * @addtogroup cFunctions
 *
 * @date 18/12/18
 */

#include <freeFunctionsAndWrappers/cStdio.h>
#include <cstdio>


namespace cFunctions
{
/*! man 3 printf */
int cStdio::snprintf(char* str
                     , size_t size
                     , const char* format
                     , ...)
{
    va_list varArg;
    va_start(varArg
             , format);
    return std::vsnprintf(str
                          , size
                          , format
                          , varArg);
}
} /* namespace cFunctions */

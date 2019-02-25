/*!
 * @brief Contains functions related to random string utility
 *
 * @date 10/28/18
 *
 * @author hmarcks
 *
 * @addtogroup utility
 */

#include <string>
#include <sstream>

namespace utility
{
/*!
 * @brief Returns a string containing nothing but count amount of c letters
 * @param count How many C's we want
 * @param c The C we want
 * @return The string containing these things
 */
std::string addXLetter(const int count
                       , const char c)
{
    std::stringstream dumString;
    for (int i = 0; i < count; ++i)
        dumString << c;

    return dumString.str();
}
/*!
 * @brief Converts A string to an int
 * @param numberStr The string that is just the number
 * @return The string as a number type
 */
long StringToLong(const std::string& numberStr)
{
    std::stringstream ss;
    ss << numberStr;
    long ret;
    ss >> ret;
    return ret;
}
} /* namespace Utility */
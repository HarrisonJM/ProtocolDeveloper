/*!
 * @brief Contains functions related to random string utility
 *
 * @date 10/28/18
 *
 * @addtogroup Utility
 */

#include <string>

/*!
 * @brief Returns a string containing nothing but count amount of c letters
 * @param count How many C's we want
 * @param c The C we want
 * @return The string containing these things
 */
std::string addXLetter(int count,
                              char c)
{
    std::string dumString;
    for(int i = 0; i < count; ++i)
        dumString.append(&c);

    return dumString;
}
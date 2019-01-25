/*!
 * @brief Contains functions related to random utility
 *
 * @date 10/28/18
 *
 * @addtogroup Utility
 */

#ifndef PROTOCOLDEVELOPER_UTILITYFUNCTIONS_H
#define PROTOCOLDEVELOPER_UTILITYFUNCTIONS_H

#include <string>

extern std::string addXLetter(int count
                              , char c);

/*!
 * @brief Converts A string to an int
 * @param numberStr The string that is just the number
 * @return The string as a number type
 */
extern long StringToLong(const std::string& numberStr);

#endif //PROTOCOLDEVELOPER_UTILITYFUNCTIONS_H

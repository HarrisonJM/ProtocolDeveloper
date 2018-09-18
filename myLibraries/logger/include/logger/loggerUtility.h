/*!
 * @brief Things used by too much to give to a specific class
 */

#ifndef PROTOCOLDEVELOPER_LOGGERUTILITY_H
#define PROTOCOLDEVELOPER_LOGGERUTILITY_H

namespace LoggerClasses {
enum class StrategyEnums : short
{
    STDOUT,
    STDERR,
    FSTREAM,
    SSTREAM
};

enum class logLevel : char
{
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

} /* namepsace LoggerClass */

#endif //PROTOCOLDEVELOPER_LOGGERUTILITY_H

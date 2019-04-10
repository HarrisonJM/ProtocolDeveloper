/*!
 * @brief Things used by too much to give to a specific class
 *
 * @author hmarcks
 * @date 10/04/19
 * @addtogroup logger
 */

#ifndef PROTOCOLDEVELOPER_LOGGERUTILITY_H
#define PROTOCOLDEVELOPER_LOGGERUTILITY_H

namespace logger {
/*!
 * @brief Selects how the log messages should be printed/to where they should be flushed
 * @{
 */
enum class StrategyEnums : short
{
    STDOUT,  /*! standard output stream */
    STDERR,  /*! standard erro stream */
    FSTREAM, /*! Filestream/to a file */
    SSTREAM  /*! string stream (mainly for testing) */
};
/*! @} */
/*!
 * @brief The severity of the message being printed
 * @{
 */
enum class logLevel : char
{
    ERROR,    /*! ERROR will be printed next to the message */
    WARNING,  /*! WARNING will be printed next to the message */
    INFO,     /*! INFO will be printed next to the message */
    DEBUG     /*! DEBUG will be printed next to the message */
};
/*! @} */
} /* namepsace logger */
/*! @} */
#endif //PROTOCOLDEVELOPER_LOGGERUTILITY_H

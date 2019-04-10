/*!
 * @brief Interface for logger class
 *
 * @author hmarcks
 *
 * @date 05 Jul 2018
 *
 * @addtogroup logger
 * @{
 * @addtogroup interfaces
 */

#ifndef PROTOCOLDEVELOPER_I_LOGGER_H
#define PROTOCOLDEVELOPER_I_LOGGER_H

#include <string>

#include "logger/loggerUtility.h"

namespace logger {

class I_LogFile
{
public:
    virtual ~I_LogFile() = default;
    /*!
     * @brief Adds a message to a log using the log ID
     * @param message The message we wish to print
     * @param lvl The severity of the message
     */
    virtual void AddLogMessage(const std::string& message
                               , logLevel lvl) = 0;
    /*!
     * @brief Grabs the oldest message from the queue
     * @return A std::string of the message
     */
    virtual std::string ReturnOldestMessage() = 0;
    /*!
     * @brief Writes The oldest message from the queue to the provided stream
     */
    virtual void WriteAllMessagesToStream() = 0;
    /*!
     * @brief Returns the latest message to be added
     * @return Returns the most recent message in the queue
     */
    virtual std::string ReturnLatestMessage() =0;
};

} /* namespace logger */
/*! @} @} */
#endif //PROTOCOLDEVELOPER_I_LOGGER_H
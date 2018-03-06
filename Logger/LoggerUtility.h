/*!
 * @brief Logger Utility Functions
 *
 * Functions used across the Logger Utility
 *
 * @ingroup Logger
 *
 * @date March 2018
 */
#include "LoggerDefinitions.h"
#include <string>

#ifndef PROTOCOLDEVELOPER_LOGGERUTILITY_H
#define PROTOCOLDEVELOPER_LOGGERUTILITY_H

namespace Logging
{
  std::string GetLogSeverity(LOGSEVERITY_T logSev);
}

#endif /* PROTOCOLDEVELOPER_LOGGERUTILITY_H */
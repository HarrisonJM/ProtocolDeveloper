/*!
 * @brief Logger Utility Functions
 *
 * Generic Functions used by different parts of the logger
 *
 * @ingroup Logger
 *
 * @date March 2018
 */
#include "LoggerUtility.h"

namespace Logging
{
    /*!
     * @brief GetLogSeverity
     * @param[in] logSev the enum dictating the severity of the entry
     *
     * @return A string that equates to the given severity
     */
  std::string GetLogSeverity(LOGSEVERITY_T logSev)
  {
      switch (logSev)
      {
          case INFO:
              return "INFO";
          case TRIVIAL:
              return "TRIVIAL";
          case ISSUE:
              return "ISSUE";
          case MAJOR:
              return "MAJOR";
          case CRITICAL:
              return "CRITICAL";
          case DEBUG:
              return "DEBUG";
          default:
              return "UNKNOWN SEVERITY GIVEN";
      }
  }
}
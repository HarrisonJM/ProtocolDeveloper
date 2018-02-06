#include "LoggerUtility.h"

namespace Logging
{
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
#include "LoggerUtility.h"

namespace Logging
{
  std::wstring GetLogSeverity(LOGSEVERITY_T logSev)
  {
      switch (logSev)
      {
          case INFO:
              return L"INFO";
          case TRIVIAL:
              return L"TRIVIAL";
          case ISSUE:
              return L"ISSUE";
          case MAJOR:
              return L"MAJOR";
          case CRITICAL:
              return L"CRITICAL";
          case DEBUG:
              return L"DEBUG";
          default:
              return L"UNKNOWN SEVERITY GIVEN";
      }
  }
}
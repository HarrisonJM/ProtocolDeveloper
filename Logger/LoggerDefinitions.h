#pragma once

namespace Logging
{

// This will be used to tack our severities
// Changes here must be tracked appropriately in Logging::Log::GetLogSeverity()
  typedef enum LOGSEVERITY
  {
      INFO,
      TRIVIAL,
      ISSUE,
      MAJOR,
      CRITICAL,
      DEBUG
  } LOGSEVERITY_T;

}
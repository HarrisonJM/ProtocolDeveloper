#ifndef __LOGGERDEFINITIONS_H__
#define __LOGGERDEFINITIONS_H__

namespace Logging
{
  /*!
   * @brief LOGSEVERITY
   *
   * enumerator list that tracks the severity of a log with a greater amount of ease
   */
  typedef enum
  {
      INFO,
      TRIVIAL,
      ISSUE,
      MAJOR,
      CRITICAL,
      DEBUG
  } LOGSEVERITY_T;

}

#endif /*__LOGGERDEFINITIONS_H__*/
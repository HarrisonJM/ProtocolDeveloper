#ifndef __LOGMOCK_H__
#define __LOGMOCK_H__

#include "../ILog.h"
#include "../LoggerDefinitions.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace Logging
{
  class MockILog: public ILog
  {
  public:
      MOCK_METHOD3(AddLog, void(LOGSEVERITY_T logSeverity, std::wstring logMessage, std::wstring testName));

      MOCK_METHOD0(getNumberOfEntries, unsigned int());
      MOCK_METHOD0(FlushQueueToFile, void());
      MOCK_METHOD0(getLogKey, std::wstring());

      MOCK_METHOD0(GenerateAndPrintLogHeader, void());
      MOCK_METHOD0(CheckLogAlreadyOpened, bool());
      MOCK_METHOD0(CheckLogAlreadyEnded, bool());
      MOCK_METHOD1(GetLogSeverity, std::wstring(LOGSEVERITY_T logSev));
      MOCK_METHOD1(WriteEntry, void(std::wstring entry));
      MOCK_METHOD0(EndLog, void());
      MOCK_METHOD1(CountNumberOfEntries, void(std::wfstream &fileToCount));
  };
}

#endif /* __LOGMOCK_H__ */
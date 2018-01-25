#include "../Log.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"



namespace Logging
{
  class logTests : public testing::Test
  {
  protected:
      // The default log object the tests will be using
      Log *log;

      virtual void SetUp()
      {
          log = new Log(L"test");
      }

      virtual void TearDown()
      {
          delete log;
      }

      void AddMessages(int numberOfMessages)
      {
          for(int i = 0; i < numberOfMessages; ++i)
          {
              log->AddLog(TRIVIAL, L"Test message " + i, L"Test name " + i);
          }
      }

  };

  TEST_F(logTests, test_ConstructorgetLogKey)
  {
      EXPECT_EQ(L"test", log->getLogKey());
  }

  TEST_F(logTests, test_AddLog)
  {
      AddMessages(1);
  }

  TEST_F(logTests, test_blah)
  {

  }

  int main(int argc, char **argv)
  {
      ::testing::InitGoogleTest(&argc, argv);

      return RUN_ALL_TESTS();
  }
}
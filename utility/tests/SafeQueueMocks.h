#include <queue>
#include "SafeQueue.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"


namespace Utility {

  template <class T>
  class SafeQueueMocks : public ::testing::Test
  {
  protected:
      MOCK_METHOD1_T(push, bool(T& newElement));
      MOCK_METHOD0_T(pop_front, T);
      MOCK_METHOD0_T(front, T);
      MOCK_METHOD0_T(back, T);
      MOCK_METHOD1_T(empty, bool());
      MOCK_METHOD0(size, size_t());
      MOCK_METHOD1_T(IsQueueFull, bool());
  };

}



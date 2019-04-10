/*!
 * @brief mocks for the TPQ
 * @addtogroup mockLibrary
 * @{
 */
#import <I_ThreadPool.h>
#include "gmock/gmock.h"

#ifndef PROTOCOLDEVELOPER_THREADPOOLMOCKS_H
#define PROTOCOLDEVELOPER_THREADPOOLMOCKS_H

class ThreadPoolMocks : public I_ThreadPool
{
    MOCK_METHOD0(initPool, void());
    MOCK_METHOD0(killPool, void());
    MOCK_METHOD0(shutdown, void());
};
/*! @} */
#endif //PROTOCOLDEVELOPER_THREADPOOLMOCKS_H

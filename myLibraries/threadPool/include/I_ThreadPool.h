/*!
 * @brief Interface for the thread pool itself
 *
 * @author hmarcks
 *
 * @date 10/04/2019
 *
 * @addtogroup threadPool
 * @{
 * @addtogroup interfaces
 * @{
 */

#ifndef PROTOCOLDEVELOPER_I_TESTTHREADPOOL_H
#define PROTOCOLDEVELOPER_I_TESTTHREADPOOL_H

#include <condition_variable>

/*!
 * @brief Thread Pool interface
 */
class I_ThreadPool
{
public:
    //I_ThreadPool(int maxQueueSize_in);
    virtual ~I_ThreadPool()
    {

    }

    // AddTaskToQueue is currently untestable
    // error: virtual function cannot have deduced return type Args&&... args);

    virtual void InitPool() = 0;
    virtual void shutdown() = 0;
};
/*! @} @} */
#endif //PROTOCOLDEVELOPER_I_TESTTHREADPOOL_H

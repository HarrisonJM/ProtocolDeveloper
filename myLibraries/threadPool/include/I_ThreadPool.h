//
// Created by hmarcks on 21/05/18.
//

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

#endif //PROTOCOLDEVELOPER_I_TESTTHREADPOOL_H

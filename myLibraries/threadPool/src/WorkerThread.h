/*!
 * @brief The thread worker that carries out tasks given to it
 *
 * @addtogroup Thread Handler
 *
 * @date 23/5/18
 */

#ifndef PROTOCOLDEVELOPER_WORKERTHREAD_H
#define PROTOCOLDEVELOPER_WORKERTHREAD_H

#include "threadPool/ThreadPool.h"
#include "I_WorkerThread.h"

namespace ThreadHandler
{
/*!
 * @brief A thread that carries out a task. Made a nested class so that it
 * can have access to the pools members
 */
class WorkerThread : public I_WorkerThread
{
public:
    /*!
     * @brief Constructor for a worker
     * @param pool_in The Threads associated Pool Queue
     * @param id_in The Threads ID
     */
    WorkerThread(ThreadPool *pool_in,
                 const int id_in);

    virtual ~WorkerThread();

    void operator()() override ;
private:
    //! @brief Pointer to the threads pool
    ThreadPool *_pool;
    //! @brief The Threads ID
    const int _ID;
};

} /* namespace ThreadHandler */

#endif /*PROTOCOLDEVELOPER_WORKERTHREAD_H*/

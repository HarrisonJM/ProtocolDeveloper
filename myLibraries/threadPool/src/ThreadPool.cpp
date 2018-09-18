/*!
 * @brief testThreadPool class handles all the systems tasks by adding nay jobs
 * to the task queue and threads will pick  up tasks to complete as necessary
 *
 * @addtogroup
 *
 */
#include "threadPool/ThreadPool.h"
#include "WorkerThread.h"

namespace ThreadHandler
{

/*!
 * @brief Constructor
 *
 * @param maxNumberOfThreadsSize_in Defines the maximum size the queue can take
 */
ThreadPool::ThreadPool(unsigned int maxNumberOfThreadsSize_in)
    :   _killPool(false),
        _threads(maxNumberOfThreadsSize_in)
{

}

/*!
 * @brief Default contructor
 */
ThreadPool::ThreadPool()
    : _killPool(false),
      _threads(0)
{

}

/*!
 * @brief Destructor
 */
ThreadPool::~ThreadPool()
{
    shutdown();
}

/*!
 * @brief Waits for threads to finish work and then shuts down
 */
void ThreadPool::shutdown()
{
    _killPool = true;
    _cond_var.notify_all();

    for ( unsigned int i = 0; i < _threads.size(); ++i)
    {
        if(_threads[i].joinable())
        {
            _threads[i].join();
        }
    }
}

/*!
 * @brief Initialises the thread pool by filling the vector with locked threads
 */
void ThreadPool::InitPool()
{
    for (unsigned int i = 0; i < _threads.size(); ++i)
    {
        _threads[i] = std::thread(WorkerThread(this, i));
    }
}

} /* namespace ThreadHandler */
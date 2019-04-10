/*!
 * @brief The thread worker that carries out tasks given to it
 *
 * @addtogroup Thread Handler
 * @{
 * @date 23/5/18
 */

#include "threadPool/ThreadPool.h"

#include "WorkerThread.h"

namespace threadPool
{
/*!
 * @brief Constructor for a worker
 * @param pool_in The Threads associated Pool Queue
 * @param id_in The Threads ID
 */
WorkerThread::WorkerThread(ThreadPool* pool_in
                           , const int id_in)
    : _standingBy(true)
      , _pool(pool_in)
      , _ID(id_in)
{
}
/*!
 * @brief Destructor
 */
WorkerThread::~WorkerThread()
{
}
/*!
 * @brief Runs the Threads. Overloading allows us to emplace an instance
 * of the class into a std::thread and start waiting for a task simultaneously
 */
void WorkerThread::operator()()
{
    //! We'll store the popped work task in here
    std::function<void()> func = nullptr;

    while (!_pool->_killPool)
    {
        //! The lock needs to be deleted
        {
            std::unique_lock<std::mutex> lock(_pool->_mutex);
            if (_pool->_taskQueue.empty())
                _pool->_cond_var.wait(lock);

            _pool->_taskQueue.pop_front(func);
        }

        if (func)
        {
            _standingBy = false;
            func();
            _standingBy = true;
        }
    }
}
/*! @} */
} /* threadPool */
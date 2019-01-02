/*!
 * @brief Implements a thread pool queue for running tests against the comms
 * handler
 *
 * @addtogroup Thread Handler
 *
 * @date 20/05/2018
 */

#ifndef PROTOCOLDEVELOPER_TESTTHREADHANDLER_H
#define PROTOCOLDEVELOPER_TESTTHREADHANDLER_H

#include <future>
#include <thread>
#include <functional>
#include <utility>
#include <mutex>
#include <vector>
#include <condition_variable>

#include "safeQueues/SafeQueue.h"
#include "I_ThreadPool.h"

namespace ThreadHandler
{

/*!
 * @brief A Thread Pool Queue that handles information that needs to be passed back and forth
 */
class ThreadPool
    : public I_ThreadPool
{
public:
    friend class WorkerThread;
    /*!
     * @brief Constructor
     *
     * @param maxNumberOfThreadsSize_in Defines the maximum size the queue can take
     */
    explicit ThreadPool(unsigned int maxNumberOfThreadsSize_in);

    /*!
     * @brief Default Constructor
     */
    ThreadPool();
    //! @brief Destructor
    virtual ~ThreadPool();

    /*!
     * @brief Inits the thread pool
     */
    void InitPool() override;

    /*!
     * @brief Adds a task (parameter bound function) to the queue
     * @tparam T A function type
     * @tparam ...Args Variadic template that holds the function parameters
     * @param t A Universal reference to a function (Scott Meyers)
     * @param args The arguments to bind/pack into the function
     */
    template<typename T, typename ...Args>
    auto AddTaskToQueue(T &&t
                        , Args &&... args) -> std::future<decltype(t(args...))>
    {
        //! Create a function that can be run
        std::function<decltype(t(args...))()>
            work = std::bind(std::forward<T>(t)
                             , std::forward<void*>(args)...);

        //! Store the function first in a packaged_task to allow asynchronous execution
        //! Store it in a shared pointer for copying
        auto work_p =
            std::make_shared<std::packaged_task<decltype(t(args...))()>>(work);

        //! Wrap as a function so it can be returned from
        std::function<void()> workWrapper = [work_p]()
        {
            (*work_p)();
        };

        //! Add task to task queue
        _taskQueue.push(workWrapper);

        //! Wake up a sleeping thread
        _cond_var.notify_one();

        //! Return the packaged_task future, due to the wrapped nature, function execution
        //! will update the future
        return work_p->get_future();
    }

    /*!
     * @brief Waits for all threads to finish and then shuts them down
     */
    void shutdown() override;

private:
    bool _killPool;
    std::vector<std::thread> _threads;

    Utility::SafeQueue<std::function<void()>> _taskQueue;

    //! @brief Stops threads from picking up the same task
    std::mutex _mutex;
    //! @brief Lets us control what threads do directly
    std::condition_variable _cond_var;
};
} /* namespace ThreadHandler */

#endif /* PROTOCOLDEVELOPER_TESTTHREADHANDLER_H */

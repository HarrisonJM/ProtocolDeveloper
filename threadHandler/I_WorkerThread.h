/*!
 * @brief Interface Representing a single testThread for sending and receiving data
 *
 * @addtogroup ThreadHandler
 *
 * @date 17/05/18
 */

#ifndef PROTOCOLDEVELOPER_I_WORKERTHREAD_H
#define PROTOCOLDEVELOPER_I_WORKERTHREAD_H

namespace ThreadHandler
{
/*!
 * @brief Thread Worker Interface
 */
class I_WorkerThread
{
public:
    /*!
     * @brief Constructor for a worker
     * @param pool_in The Threads associated Pool Queue
     * @param id_in The Threads ID
     */
    virtual ~I_WorkerThread()
    {

    }

    /*!
     * @brief Runs the Threads
     */
    virtual void operator()() = 0;
};

} /* namespace ThreadHandler */

#endif //PROTOCOLDEVELOPER_I_WORKERTHREAD_H

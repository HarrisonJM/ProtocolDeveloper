/*!
 * @brief SafeQueue
 *
 *  A thread safe queue wrapper.
 *
 *  @addtogroup Utility
 *
 *  @date March 2018
 *
 */
#ifndef PROTOCOLDEVELOPER_SAFEQUEUE_H
#define PROTOCOLDEVELOPER_SAFEQUEUE_H

#include <queue>
#include <mutex>

namespace SafeContainers {
/*!
 * @brief SafeQueue
 *
 * @tparam T The type of object it'll be storing
 */
template<class T>
class SafeQueue
{
public:
    /*!
     * @brief Default constructor
     *
     * Default constructor. Assigns a 16k buffer to the queue
     */
    SafeQueue()
    {
        // Constructor
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief Default destructor
     */
    virtual ~SafeQueue()
    {
        // Destructor
        while(!_basic_q.empty())
        {
            T t;
            pop_front(t);
        }
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief push
     *
     * Pushes a new element to the back of the queue
     *
     * @param newElement A reference containing what is to be written to queue
     *
     * @return ture if successfully added to the queue, otherwise false
     */
    virtual bool push(T& newElement)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _basic_q.push(newElement);

        return true;
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief Returns the element from the front of the queue and removes it
     *
     * @return The value from the front of the queue
     */
    virtual void pop_front(T& t)
    {
        if(!_basic_q.empty())
        {
            t = std::move(_basic_q.front());
            _basic_q.pop();
        }
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief Creates a class in place and places at the back of the queue
     *
     * @tparam Args Move type?
     * @param args Args with which to build the thing?
     * @return None
     */
    template<class... Args>
    void emplace(Args&&... args)
    {
        // Construct an element in place and then push
        std::unique_lock<std::mutex> lock(_mut);
        _basic_q.emplace(args...);
    }

    //-------------------------------------------------------------------------

    /*!
     * @brief front
     *
     * Returns a copy of the front element of the queue
     *
     * @return A copy of the element at the front of the queue
     */
    virtual T front()
    {
        // Return the element at the front of the queue
        return _basic_q.front();
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief back
     *
     * @return a copy of the last element of the queue
     */
    virtual T back()
    {
        // Return the element at the back of the queue
        return _basic_q.back();
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief empty
     *
     * Checks to see if the queue is empty, returning true or false, dependent
     *
     * @return true if queue is full
     */
    virtual bool empty()
    {
        // Returns true if empty
        return _basic_q.empty();
    }

    //-------------------------------------------------------------------------
    // Returns the number of elements of the queue
    /*!
     * @brief Returns the number of elements in the queue
     *
     * @return The number of elements int he queue
     */
    virtual size_t size()
    {
        return _basic_q.size();
    }

    //-------------------------------------------------------------------------

    //! @TODO: May need operator overloading for comparison
    //! @TODO: May need extra constructors

    //-------------------------------------------------------------------------

private:
    //! the queue storage
    std::queue<T> _basic_q;
    //! The mutex
    std::mutex _mut;
};

} /* namespace SafeContainers */

#endif /* PROTOCOLDEVELOPER_SAFEQUEUE_H */

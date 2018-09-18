/*!
 * @brief SafeQueue but with a maximum buffer size
 *
 * @addtogroup Utility
 *
 * @date 20/05/2018
 *
 */

#ifndef PROTOCOLDEVELOPER_SAEFQUEUEBUFFERSIZE_H
#define PROTOCOLDEVELOPER_SAEFQUEUEBUFFERSIZE_H

#include <queue>
#include <mutex>

namespace Utility
{
/*!
 * @brief SafeQueueBufferSize
 *
 * @tparam T The type of object it'll be storing
 */
template<class T>
class SafeQueueBufferSize
{
public:
    /*!
     * @brief Default constructor
     *
     * Default constructor. Assigns a 16k buffer to the queue
     */
    SafeQueueBufferSize()
        : _maximumBufferSize(16384),
          _currentBufferSize(0),
          _Tsize(sizeof(T))
    {
        // Constructor
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief Buffer Size Constructor
     *
     * Assigns the maximum buffer size to whatever is passed
     *
     * @param in_MaxBuff The maximum size (in bytes) that the logs buffer can be
     */
    SafeQueueBufferSize(size_t in_MaxBuff)
        : _maximumBufferSize(in_MaxBuff),
          _currentBufferSize(0),
          _Tsize(sizeof(T))
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
            T t = pop_front();
            delete[] t;
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
        if (IsQueueFull())
            return false;

        std::unique_lock<std::mutex> lock(_mut);
        _currentBufferSize += _Tsize;
        _basic_q.push(newElement);

        return true;
    }

    //-------------------------------------------------------------------------
    /*!
     * @brief pop_front
     *
     * Returns the element from the front of the queue and removes it
     *
     * @return Returns the value from the front of the queue
     */
    virtual T pop_front()
    {
        // Return an element and remove from queue
        T element;
        if (!_basic_q.empty())
        {
            std::unique_lock<std::mutex> lock(_mut);
            element = _basic_q.front();
            _basic_q.pop();
            _currentBufferSize -= _Tsize;
        }
        else
            element = NULL;

        return element;
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
        _currentBufferSize += sizeof(args);
        _basic_q.emplace(args);
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
     * Returns a copy of the last element of the queue
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
    // Returns the size of the queue (in bytes)
    /*!
     * @brief Returns the size of the queue in bytes
     *
     * @return The number of elements in the queue
     */
    virtual size_t realSize()
    {
        return (_basic_q.size() * sizeof(T));
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
    //! The maximum size (in bytes) we want the queue to be
    const size_t _maximumBufferSize;
    //! The maximum size (in bytes) we want the queue to be
    size_t _currentBufferSize;
    //?! The size of the object we're storing
    const size_t _Tsize;

    /*!
     * @brief Checks to see if the max buffer size has been reached
     *
     * @return True of full, otherwise false
     */
    virtual bool IsQueueFull()
    {
        if (_currentBufferSize >= _maximumBufferSize)
            return true;

        return false;
    }
};

}

#endif //PROTOCOLDEVELOPER_SAEFQUEUEBUFFERSIZE_H

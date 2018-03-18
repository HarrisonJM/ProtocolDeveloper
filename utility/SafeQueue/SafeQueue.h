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

// This will declare the thread safe queue I'll be using

namespace Utility {
    /*!
     * @brief typedef'ing to unsigned int size_t
     */
    typedef long unsigned int size_t;
    /*!
     * @brief SafeQueue
     *
     * @tparam T The type of object it'll be storing
     */
    template<class T>
    class SafeQueue
    {
    protected:
        // Private methods below public methods
        //! the queue storage
        std::queue<T> basic_q;
        //! The mutex
        std::mutex mut;
        //! The maximum size (in bytes) we want the queue to be
        size_t MaximumBufferSize;

    public:
        /*!
         * @brief Default constructor
         *
         * Default constructor. Assigns a 16k buffer to the queue
         */
        SafeQueue() : MaximumBufferSize(16384)
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
        SafeQueue(size_t in_MaxBuff)
            : MaximumBufferSize(in_MaxBuff)
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
            if (!basic_q.empty())
            {
                // Delete the objects
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
            if (IsQueueFull() == true)
                return false;

            std::unique_lock<std::mutex> lock(mut);
            basic_q.push(newElement);

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
            if (!basic_q.empty())
            {
                std::unique_lock<std::mutex> lock(mut);
                element = basic_q.front();
                basic_q.pop();
            }

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
            std::unique_lock<std::mutex> lock(mut);
            basic_q.emplace(args);
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
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.front();
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
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.back();
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
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.empty();
        }

        //-------------------------------------------------------------------------
        // Returns the number of elements of the queue
        /*!
         * @brief size
         *
         * Returns the number of elements in the queue
         * @todo figure out how to get the size (in bytes) of whatever is stored
         *
         * @return The number of elements int he queue
         */
        virtual size_t size()
        {
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.size();
        }

        //-------------------------------------------------------------------------

        //! @TODO: May need operator overloading for comparison
        //! @TODO: May need extra constructors

        //-------------------------------------------------------------------------

    private:
        // Checks to see if the queues maximum size has been reached
        /*!
         * @brief IsQueueFull
         *
         * Checks to see if the max buffer size has been reached
         *
         * @return True of full, otherwise false
         */
        virtual bool IsQueueFull()
        {
            //! \TODO: Check size of buffer
            return false;
        }

        //-------------------------------------------------------------------------
    };
}

#endif /* PROTOCOLDEVELOPER_SAFEQUEUE_H */

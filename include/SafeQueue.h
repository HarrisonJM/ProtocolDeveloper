#pragma once
#include <queue>
#include <mutex>

// This will declare the thread safe queue I'll be using

namespace Utility {
    typedef long unsigned int size_t;
    template<class T>
    class SafeQueue
    {
    private:
        // Private methods below public methods
        std::queue<T> basic_q;
        std::mutex mut;
        size_t MaximumBufferSize;

    public:
        // Default constructor
        SafeQueue() : MaximumBufferSize(16384)
        {
            // Constructor
        }

        //-------------------------------------------------------------------------
        // User defined maximum queue size
        SafeQueue(size_t in_MaxBuff)
            : MaximumBufferSize(in_MaxBuff)
        {
            // Constructor
        }

        //-------------------------------------------------------------------------

        ~SafeQueue()
        {
            // Destructor
            if (!basic_q.empty())
            {
                // Delete the objects
            }
        }

        //-------------------------------------------------------------------------
        // Pushes a new element to the back of the queue
        bool push(T& newElement)
        {
            if (IsQueueFull() == true)
                return false;

            std::unique_lock<std::mutex> lock(mut);
            basic_q.push(newElement);

            return true;
        }

        //-------------------------------------------------------------------------
        // Returns the element from the front of the queue and remvoes it
        T pop_front()
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
        
        // TODO: work out why it won't build
        //-------------------------------------------------------------------------
        // Creaets a class in place and places at the of the queue
        //template<class ...Args>
        //bool emplace(Args&&... args)
        //{
        //    // Construct an element in place and then push
        //    std::unique_lock<std::mutex> lock(mut);
        //    basic_q.emplace(args);
        //}

        //-------------------------------------------------------------------------
        // Returns a copy of the front element of the queue
        T front()
        {
            // Return the element at the front of the queue
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.front();
        }

        //-------------------------------------------------------------------------
        // returns a copy of the last element of the queue
        T back()
        {
            // Return the element at the back of the queue
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.back();
        }

        //-------------------------------------------------------------------------
        // returns whether or not the queue is empty. True if it is empty
        bool empty()
        {
            // Returns true if empty
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.empty();
        }

        //-------------------------------------------------------------------------
        // Returns the number of elements of the queue
        size_t size()
        {
            std::unique_lock<std::mutex> lock(mut);
            return basic_q.size();
        }

        //-------------------------------------------------------------------------

        //! \TODO: May need operator overloading for comparison
        //! \TODO: May need extra constructors

    private:
        // Checks to see if the queues maximum size has been reached
        bool IsQueueFull()
        {
            //! \TODO: Check size of buffer
            return false;
        }

        //-------------------------------------------------------------------------
    };
}
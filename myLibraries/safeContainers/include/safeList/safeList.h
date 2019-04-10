/*!
 * @brief A thread-safe list
 *
 * @author hmarcks
 *
 * @addtogroup safeContainers
 * @{
 * @addtogroup safeList
 * @{
 * @date 16/01/19
 */


#ifndef PROTOCOLDEVELOPER_SAFELIST_H
#define PROTOCOLDEVELOPER_SAFELIST_H

#include <list>
#include <mutex>
#include <memory>

namespace safeContainers
{
/*!
 * @brief A thread safe queue
 * @tparam T The type the list should take
 */
template<typename T>
class safeList
{
public:
    /*!
     * @brief Constrctor
     */
    safeList()
        : _list(std::make_shared<std::list<T>>())
          , _useDestructor(true)
    {
        _mut.unlock();
    }
    /*!
     * @brief Constructor
     * @param list_in The list we want to use
     */
    explicit safeList(std::shared_ptr<std::list<T>> list_in)
        : _list(list_in)
          , _useDestructor(true)
    {
    }
    ~safeList() = default;

    /* Modifiers */
    /*!
     * @brief pushes value to fron of the list
     * @param val The value we want to push
     */
    void push_front(const T& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.push_front(val);
    }
    /*!
     * @brief pushes value to fron of the list
     * @param val The value we want to push
     */
    void push_front(T&& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.push_front(val);
    }
    /*!
     * @brief pops value from the front of the list
     */
    void pop_front()
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.pop_front();
    }
    /*!
     * @brief pushes value to back of the list
     * @param val The value we want to push
     */
    void push_back(const T& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list->push_back(val);
    }
    /*!
     * @brief pushes value to back of the list
     * @param val The value we want to push
     */
    void push_back(T&& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list->push_back(val);
    }
    /*!
     * @brief pops value to back of the list
     */
    void pop_back()
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.pop_back();
    }

    /* Element Access */
    /*!
     * @brief Gets a reference to the value at the front of the list
     * @return A reference to the value at the front of the list
     */
    T& front()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.front();
    }
    /*!
     * @brief Gets a reference to the value at the back of the list
     * @return A reference to the value at the back of the list
     */
    T& back()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.back();
    }

    /* Capacity */
    /*!
     * @brief Is the list empty
     * @return true for empty
     */
    bool empty() noexcept
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.empty();
    }
    /*!
     * @brief How many elemnts are in the list
     * @return The number of elements in the list
     */
    size_t size() noexcept
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list->size();
    }
    /*!
     * @brief What is the maxmium size of the list
     * @return The maximum size of the list
     */
    size_t max_size() noexcept
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.max_size();
    }

    /* Merge lists */
    /*!
     * @brief Merges this list with another
     * @param x The list we wish to merge with
     */
    void merge(std::list<T>& x)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.merge(x);
    }
    /*!
     * @brief Merges this list with another
     * @param x The list we wish to merge with
     */
    void merge(std::list<T>&& x)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.merge(x);
    }

    /* Iterators */
    typedef typename std::list<T>::iterator iterator;
    iterator begin()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.begin();
    }
    iterator end()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.end();
    }
    typedef typename std::list<T>::const_iterator const_iterator;
    const_iterator cbegin()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.cbegin();
    }
    const_iterator cend()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.end();
    }

    /*!
     * @brief Returns the underlying list container (for merging)
     * @return A reference to the underlying std::list
     */
    std::list<T>& getList()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list;
    }
private:
    std::shared_ptr<std::list<T>> _list;
    bool _useDestructor;
    std::mutex _mut;
};

} /* namespace safeContainers */
/*! @} @} */
#endif /* PROTOCOLDEVELOPER_SAFELIST_H */

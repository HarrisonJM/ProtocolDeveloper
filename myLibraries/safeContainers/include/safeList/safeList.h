/*!
 * @brief A thread-safe list
 *
 * @author hmarcks
 *
 * @addtogroup Utility
 *
 * @date 16/01/19
 */


#ifndef PROTOCOLDEVELOPER_SAFELIST_H
#define PROTOCOLDEVELOPER_SAFELIST_H

#include <list>
#include <mutex>

namespace SafeContainers
{
/*!
 * @brief A thread safe queue
 * @tparam T The type the list should take
 */
template<typename T>
class safeList
{
public:
    safeList()
        : _lock(_mut)
          , _list(std::shared_ptr<std::list<T>>())
          , _useDestructor(true)
    {
    }
    explicit safeList(std::shared_ptr<std::list<T>> list_in)
        : _lock(_mut)
          , _list(list_in)
          , _useDestructor(true)
    {
    }
    ~safeList() = default;

    /* Modifiers */
    void push_front(const T& val)
    {
        _lock.lock();
        _list.push_front(val);
    }
    void push_front(T&& val)
    {
        _lock.lock();
        _list.push_front(val);
    }
    void pop_front()
    {
        _lock.lock();
        _list.pop_front();
    }
    void push_back(const T& val)
    {
        _lock.lock();
        _list->push_back(val);
    }
    void push_back(T&& val)
    {
        _lock.lock();
        _list.push_back(val);
    }
    void pop_back()
    {
        _lock.lock();
        _list.pop_back();
    }

    /* Element Access */
    T& front()
    {
        _lock.lock();
        return _list.front();
    }
    T& back()
    {
        _lock.lock();
        return _list.back();
    }

    /* Capacity */
    bool empty() noexcept
    {
        _lock.lock();
        return _list.empty();
    }
    size_t size() noexcept
    {
        _lock.lock();
        return _list.size();
    }
    size_t max_size() noexcept
    {
        _lock.lock();
        return _list.max_size();
    }

    /* Merge lists */
    void merge(std::list<T>& x)
    {
        _lock.lock();
        _list.merge(x);
    }
    void merge(std::list<T>&& x)
    {
        _lock.lock();
        _list.merge(x);
    }

    /* Iterators */
    typedef typename std::list<T>::iterator iterator;
    iterator begin()
    {
        _lock.lock();
        return _list.begin();
    }
    iterator end()
    {
        _lock.lock();
        return _list.end();
    }
    typedef typename std::list<T>::const_iterator const_iterator;
    const_iterator cbegin()
    {
        _lock.lock();
        return _list.cbegin();
    }
    const_iterator cend()
    {
        _lock.lock();
        return _list.end();
    }

    /*!
     * @brief Returns the underlying list container (for merging)
     * @return A reference to the underlying std::list
     */
    std::list<T>& getList()
    {
        _lock.lock();
        return _list;
    }
private:
    std::unique_lock<std::mutex> _lock;
    std::shared_ptr<std::list<T>> _list;
    bool _useDestructor;
    std::mutex _mut;
};
} /* namespace SafeContainers */

#endif /* PROTOCOLDEVELOPER_SAFELIST_H */

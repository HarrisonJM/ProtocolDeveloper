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
#include <memory>

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
        : _list(std::make_shared<std::list<T>>())
          , _useDestructor(true)
    {
        _mut.unlock();
    }
    explicit safeList(std::shared_ptr<std::list<T>> list_in)
        : _list(list_in)
          , _useDestructor(true)
    {
    }
    ~safeList() = default;

    /* Modifiers */
    void push_front(const T& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.push_front(val);
    }
    void push_front(T&& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.push_front(val);
    }
    void pop_front()
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.pop_front();
    }
    void push_back(const T& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list->push_back(val);
    }
    void push_back(T&& val)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list->push_back(val);
    }
    void pop_back()
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.pop_back();
    }

    /* Element Access */
    T& front()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.front();
    }
    T& back()
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.back();
    }

    /* Capacity */
    bool empty() noexcept
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.empty();
    }
    size_t size() noexcept
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list->size();
    }
    size_t max_size() noexcept
    {
        std::unique_lock<std::mutex> lock(_mut);
        return _list.max_size();
    }

    /* Merge lists */
    void merge(std::list<T>& x)
    {
        std::unique_lock<std::mutex> lock(_mut);
        _list.merge(x);
    }
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

} /* namespace SafeContainers */

#endif /* PROTOCOLDEVELOPER_SAFELIST_H */

/*!
 * @brief Defines a thread safe type
 *
 * @author hmarcks
 *
 * @addtogroup utility
 * @{
 * @addtogroup threadSafeT
 * @{
 *
 * @date 17/01/19
 *
 * @todo figure out why the overloads won't behave...
 */
#ifndef PROTOCOLDEVELOPER_THREADSAFEBOOL_H
#define PROTOCOLDEVELOPER_THREADSAFEBOOL_H

#include <mutex>

namespace utility
{
/*!
 * @brief Allows for basic thread safe access to some type
 * @tparam T The type the class should protect
 */
template<typename T>
class ThreadSafeT
{
public:
    /*!
     * @brief Constructor
     * @param initial The initial value the value should take
     */
    ThreadSafeT(T initial)
        : _internal(initial)
        , _mut()
//        , _lock(_mut)
    {
    }
    /*!
     * @brief Destructor
     */
    ~ThreadSafeT() = default;
    /*!
     * @brief Returns the internal T store
     * @return The current value of T
     */
    T GetT()
    {
        std::lock_guard<std::mutex> _lock(_mut);
        return _internal;
    }
    /*!
     * @brief Sets the internal T variable
     * @param newVal The new value that T should take
     * @return A reference to itself
     */
    void SetT(T newVal)
    {
        std::lock_guard<std::mutex> _lock(_mut);
        _internal = newVal;
    }
    /*!
     * @brief Implicit conversion operator for easier use in ifs
     * @return The internally stored bool
     */
    operator bool() const
    {
        return _internal;
    }
//    /*!
//     * @brief Should allow simple assignment
//     * @param other The new value we're setting
//     * @return A reference to itself
//     */
//    T& operator=(const T& other)
//    {
//        return SetT(other);
//    }
private:
    /*! @brief The type variable itself */
    T _internal;
    /*! @brief The mutex used to protect the type */
    mutable std::mutex _mut;
};

} /* namespace safeContainers */
/*! @} @} */
#endif /* PROTOCOLDEVELOPER_THREADSAFEBOOL_H */

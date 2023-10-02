#ifndef SMART_PTR_HXX
#define SMART_PTR_HXX

#include "smart_ptr.hpp"

#include <stdexcept>
#include <utility> //swap
#include <exception> 

namespace Ptr {

template<typename T>
SmartPtr<T>::SmartPtr(T* a_ptr)
: m_ptr{a_ptr}
{
}

template<typename T>
SmartPtr<T>::~SmartPtr() noexcept
{
    delete m_ptr;
}

template<typename T>
T& SmartPtr<T>::operator*()
{
    if (!m_ptr) {
        throw:: std::runtime_error("null ptr");
    }
    return *m_ptr;
}

template<typename T>
T const& SmartPtr<T>::operator*() const
{
    if (!m_ptr) {
        throw:: std::exception();
    }
    return *m_ptr; 
}

template<typename T>
T const* SmartPtr<T>::operator->() const
{
    return m_ptr; 
}

template<typename T>
T* SmartPtr<T>::operator->()
{ 
    return m_ptr;
}

template<typename T>
SmartPtr<T>::operator bool() const
{ 
    return m_ptr != nullptr;
}

template<typename T>
SmartPtr<T>::SmartPtr(SmartPtr&& a_other) noexcept
: m_ptr{a_other.m_ptr}
{
    a_other.m_ptr = nullptr;
}

template<typename T>
void SmartPtr<T>::swap(SmartPtr& a_other)
{
    std::swap(m_ptr, a_other.m_ptr);
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr&& a_other) noexcept
{
    if(this != &a_other){
        SmartPtr c(std::move(a_other));
        swap(c);
    }
    return *this;
}

template<typename T>
bool SmartPtr<T>::operator==(SmartPtr const& a_other) const noexcept
{
    return m_ptr == a_other.m_ptr;
}

template<typename T>
bool SmartPtr<T>::operator!=(SmartPtr const& a_other) const noexcept
{
    return m_ptr != a_other.m_ptr;
}

template<typename T>
SmartPtr<T>::operator void*()
{
    return (void*)m_ptr;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, SmartPtr<U> const& a_ptr) {
    if (a_ptr.m_ptr)
        os << a_ptr.m_ptr;
    return os;
}

} //namespace Ptr

#endif // SMART_PTR_HXX


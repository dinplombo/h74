#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP

#include <iostream> //ostream

namespace Ptr {

template<typename T>
class SmartPtr {
public:
    explicit SmartPtr(T* a_ptr = nullptr);

    ~SmartPtr() noexcept;
    SmartPtr(SmartPtr&& a_other) noexcept;
    SmartPtr& operator=(SmartPtr&& a_other) noexcept;
    SmartPtr(SmartPtr& a_other) = delete;
    SmartPtr& operator=(SmartPtr const& a_other) = delete;

    T& operator*();
    T* operator->();
    T const& operator*() const;
    T const* operator->() const;
    
    explicit operator bool() const;
    void swap(SmartPtr& a_other);

    bool operator==(SmartPtr const& a_other) const noexcept;
    bool operator!=(SmartPtr const& a_other) const noexcept;
    operator void*();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, SmartPtr<U> const& a_ptr);
private:
    T* m_ptr;
};

template<typename U>
std::ostream& operator<<(std::ostream& os, SmartPtr<U> const& a_ptr);



} //namespace Ptr

#include "inl/smart_ptr.hxx"

#endif // SMART_PTR_HPP
#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include "blocking_queue.hpp"

#include <cstddef> //size_t
#include <cassert> //assert 

#include <queue> 
#include <mutex> //lock guard unique_lock
#include <condition_variable> //wait notify
#include <memory> //move

namespace ds_thread_safe {

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_capacity{a_capacity}
, m_data{}
, cv_enqueue{}
, cv_dequeue{}
, cv_m{}
{
}

template <typename T>
size_t BlockingQueue<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
size_t BlockingQueue<T>::size() const 
{
    std::lock_guard<std::mutex> lk(cv_m);
    return m_data.size();
}

template <typename T>
bool BlockingQueue<T>::empty() const 
{
    std::lock_guard<std::mutex> lk(cv_m);
    return m_data.size() == 0;
}

template <typename T>
bool BlockingQueue<T>::full() const 
{
    std::lock_guard<std::mutex> lk(cv_m);
    return m_capacity == m_data.size();
}

template <typename T>
BlockingQueue<T>& BlockingQueue<T>::enqueue(T&& a_item)   
{
    std::unique_lock<std::mutex> lk(cv_m);

    while(m_capacity == m_data.size()){
        cv_enqueue.wait(lk);
    }

    m_data.push(std::move(a_item));
    cv_dequeue.notify_all();
    return *this;
}

template <typename T>
BlockingQueue<T>& BlockingQueue<T>::enqueue(T const& a_item)   
{
    std::unique_lock<std::mutex> lk(cv_m);

    while(m_capacity == m_data.size()){
        cv_enqueue.wait(lk);
    }

    m_data.push(a_item);
    cv_dequeue.notify_all();
    return *this;
}

template <typename T>
BlockingQueue<T>& BlockingQueue<T>::dequeue(T& a_begin) 
{
    std::unique_lock<std::mutex> lk(cv_m);

    while(m_data.size() == 0){
        cv_dequeue.wait(lk);
    }

    a_begin = std::move((m_data.front()));
    m_data.pop();
    cv_enqueue.notify_all();
    
    return *this;
}

}//namespace ds_thread_safe

#endif // BLOVCING_QUEUE_HXX
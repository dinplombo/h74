#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <cstddef> //size_t

#include <queue> 
#include <mutex> //mutex
#include <condition_variable> //condition_variable 

namespace ds_thread_safe {

template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t a_capacity); 

    ~BlockingQueue() noexcept = default;
    BlockingQueue(BlockingQueue const& a_other) = delete;
    BlockingQueue(BlockingQueue&& a_other) = delete;
    BlockingQueue& operator=(BlockingQueue const& a_other) = delete;
    BlockingQueue& operator=(BlockingQueue&& a_other) = delete;

    BlockingQueue& enqueue(T&& a_item);
    BlockingQueue& enqueue(T const& a_item);
    BlockingQueue& dequeue(T& a_begin);

    size_t capacity() const noexcept;
    size_t size() const;
    bool empty() const;
    bool full() const;

private:
    size_t m_capacity;
    std::queue<T> m_data;
    std::condition_variable cv_enqueue;
    std::condition_variable cv_dequeue;
    mutable std::mutex cv_m;
};

}//namespace ds_thread_safe

#include "inl/blocking_queue.hxx"

#endif // BLOVCING_QUEUE_HPP

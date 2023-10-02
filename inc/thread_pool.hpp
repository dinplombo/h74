#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include "blocking_queue.hpp" 
#include "task.hpp" 

#include <cstddef> //size_t

#include <vector> 
#include <set> 
#include <thread> 
#include <memory>  //unique_ptr
#include <mutex>  
#include <condition_variable> 

using namespace ds_thread_safe;
using namespace task;

namespace concurrency {

class ThreadPool {
public:
    explicit ThreadPool(size_t a_thred_num =  std::thread::hardware_concurrency() - 1, size_t a_capacity = 1024); 

    ~ThreadPool();
    // ThreadPool(ThreadPool const& a_other) = delete;
    // ThreadPool(ThreadPool&& a_other) = delete;
    // ThreadPool& operator=(ThreadPool const& a_other) = delete;
    // ThreadPool& operator=(ThreadPool&& a_other) = delete;

    size_t threads() const;
    void submit(std::unique_ptr<Task>&& a_task);
    void shutdown();
    void shutdown_immediate();
    void add(size_t a_thread_num);
    void remove(size_t a_thread_num);

private:
    friend class ShutDown;
    friend void work(ThreadPool& a_threaf_pool);

private:
    BlockingQueue<std::unique_ptr<Task>> m_task_container;
    std::vector<std::thread> m_thread_pool;
    size_t m_thread_num;
    bool m_shutdowm;
    bool m_remove;
    bool m_shutdown_immediate;
    mutable std::mutex m_mtx;
    size_t m_remove_counter; 
    std::condition_variable m_cv; 
    std::set<std::thread::id> m_thread_id;
};

class ShutDown : public Task {
public:
    explicit ShutDown(ThreadPool& a_threaf_pool);

    void operator()() override;

private:
    ThreadPool& m_threaf_pool;
};

void work(ThreadPool& a_threaf_pool);

}//namespace concurrency

#endif // THREAD_POOL_HPP

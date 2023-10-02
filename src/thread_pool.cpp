#include "thread_pool.hpp"

#include "my_execption.hpp"

#include <cstddef> //size_t
#include <thread> //thread
#include <memory> //move
#include <functional> //ref
#include <iostream> //ref

namespace concurrency {

void work(ThreadPool& a_thread_pool)
{
    for(;;){
        if(a_thread_pool.m_remove && a_thread_pool.m_remove_counter == 0){
                std::unique_lock<std::mutex> lk(a_thread_pool.m_mtx);
                a_thread_pool.m_remove = false;
                a_thread_pool.m_cv.notify_one();
        }
        std::unique_ptr<Task> t;
        a_thread_pool.m_task_container.dequeue(t);
        try {
            (*t)();
            } catch (...){
                return;
            }
        if(a_thread_pool.m_shutdowm){
            break;
        }
        if(a_thread_pool.m_shutdown_immediate){
            break;
        }
        if(a_thread_pool.m_remove_counter){
            std::lock_guard<std::mutex> lk(a_thread_pool.m_mtx);
            --a_thread_pool.m_remove_counter;
            a_thread_pool.m_remove = true;
            a_thread_pool.m_thread_id.insert(std::this_thread::get_id());
            
            break;
        }
    }
}

ThreadPool::ThreadPool(size_t a_thread_num, size_t a_capacity)
: m_task_container{a_capacity}
, m_thread_pool{}
, m_thread_num{a_thread_num}
, m_shutdowm{false}
, m_remove{false}
, m_shutdown_immediate{false}
, m_mtx{}
, m_remove_counter{}
, m_cv{}
, m_thread_id{}
{
    m_thread_pool.reserve(a_thread_num);
    for(size_t i = 0; i < a_thread_num; ++i){
        m_thread_pool.emplace_back(std::move(std::thread(work, std::ref(*this))));
    }
}

void ThreadPool::submit(std::unique_ptr<Task>&& a_task)
{
    if(!m_shutdowm){
        m_task_container.enqueue(std::move(a_task));
    }
}

ThreadPool::~ThreadPool()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    for (auto& t : m_thread_pool){
        t.join();
    }
}

size_t ThreadPool::threads() const
{
    std::lock_guard<std::mutex> lk(m_mtx);
    return m_thread_num;
}

void ThreadPool::shutdown()
{
    std::lock_guard<std::mutex> lk(m_mtx);
    for(size_t i = 0; i < m_thread_num; ++i){
        std::unique_ptr<Task> task = std::make_unique<ShutDown>(*this);
        m_task_container.enqueue(std::move(task));
    }
    for (auto& t : m_thread_pool){
        t.join();
    }
    m_thread_pool.clear();
}   

void ThreadPool::add(size_t a_thread_num)
{
    std::lock_guard<std::mutex> lk(m_mtx);
    m_thread_num += a_thread_num;
     for(size_t i = 0; i < a_thread_num; ++i){
        m_thread_pool.emplace_back(std::move(std::thread(work, std::ref(*this))));
    }
}

void ThreadPool::remove(size_t a_thread_num)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    m_remove_counter = a_thread_num; 
    m_cv.wait(lk);
    auto itr_thread = m_thread_pool.begin();
    while(itr_thread != m_thread_pool.end()){
        auto it = m_thread_id.find((*itr_thread).get_id());
        if(it != m_thread_id.end()){
            (*itr_thread).join();
            m_thread_pool.erase(itr_thread);
            --m_thread_num;
            m_thread_id.erase(it);
        } else {
            ++itr_thread;
        }
    }
}

void ThreadPool::shutdown_immediate()
{
    std::lock_guard<std::mutex> lk(m_mtx);
    m_shutdown_immediate = true;
    for(size_t i = 0; i < m_thread_num; ++i){
        std::unique_ptr<Task> task = std::make_unique<ShutDown>(*this);
        m_task_container.enqueue(std::move(task));
    }
    for (auto& t : m_thread_pool){
        t.join();
    }
    m_thread_pool.clear();
}

ShutDown::ShutDown(ThreadPool& a_threaf_pool)
: m_threaf_pool{a_threaf_pool}
{
}

void ShutDown::operator()() 
{  
    m_threaf_pool.m_shutdowm = true;
}

}//namespace concurrency



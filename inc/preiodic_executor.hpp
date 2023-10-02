#ifndef PERIODIC_EXECUTOR_HPP
#define PERIODIC_EXECUTOR_HPP

#include "task.hpp"
#include "thread.hpp"

#include <chrono>
#include <ctime>
#include <algorithm>
#include <functional>
#include <vector>
#include <thread> //sleep_until
// #include <memory>

using namespace thread;
using namespace task;


namespace threading {

namespace{

template <typename Clock>
struct PeriodicTask {
    Task* m_task;
    std::chrono::time_point<Clock> m_next_time;
    std::chrono::milliseconds m_delay;
    std::chrono::milliseconds m_period;
};


template <typename Clock>
bool operator<(PeriodicTask<Clock> const& a_lhs, PeriodicTask<Clock> const& a_rhs)
{
    return a_lhs.m_next_time < a_rhs.m_next_time;
}

template <typename Clock>
class CyclicExecutor {
public:
    CyclicExecutor(std::vector<PeriodicTask<Clock>>& a_tasks);

    void operator()();

private:
    std::vector<PeriodicTask<Clock>>& m_tasks;
};

template <typename Clock>
CyclicExecutor<Clock>::CyclicExecutor(std::vector<PeriodicTask<Clock>> &a_tasks)
:m_tasks{a_tasks}
{
}

template <typename Clock>
void CyclicExecutor<Clock>::operator()()
{
    while(not m_tasks.empty()){
        auto it = m_tasks.begin();
        auto& task = *it;
        std::this_thread::sleep_until(task.m_next_time);

        try{
            auto need_run = task.m_task->run();
            if (need_run){
                task.m_next_time += task.m_period;
                std::make_heap(it, m_tasks.end());
            } else{
                std::pop_heap(it, m_tasks.end());
                m_tasks.pop_back();
            }
        } catch(...){
            std::pop_heap(it, m_tasks.end());
            m_tasks.pop_back();
        }
    }
}

} //namespace

template<typename Clock>
class PeriodicExecutor {
public:
    PeriodicExecutor(size_t a_capacity = 5);

    ~PeriodicExecutor() noexcept = default;
    PeriodicExecutor(PeriodicExecutor const& a_other) = delete;
    PeriodicExecutor& operator=(PeriodicExecutor const& a_other) = delete;

    void add(Task& a_task, size_t a_delay, size_t a_period);
    void start() noexcept; 

private:
    enum class State {Adding, Runnig};

private:
    State m_state;
    std::vector<PeriodicTask<Clock>> m_tasks;
    Thread<CyclicExecutor<Clock>> m_executor;
};

template <typename Clock>
PeriodicExecutor<Clock>::PeriodicExecutor(size_t a_capacity)
: m_state{State::Adding}
, m_tasks{}
, m_executor{CyclicExecutor{m_tasks}}
{
    m_tasks.reserve(a_capacity);
}

template <typename Clock>
void PeriodicExecutor<Clock>::add(Task &a_task, size_t a_delay, size_t a_period)
{
    if (m_state == State::Adding){
        auto delay = std::chrono::milliseconds(a_delay);
        auto period = std::chrono::milliseconds(a_period);
        auto task = PeriodicTask<Clock>{&a_task, {}, {delay}, {period}};
        m_tasks.push_back(task);
    }
}

template <typename Clock>
void PeriodicExecutor<Clock>::start() noexcept
{
    if (m_state == State::Runnig){
        return;
    }

    m_state = State::Runnig;
    for(auto& task : m_tasks) {
        task.m_next_time =  Clock::now() + task.m_delay;
    }

    std::make_heap(m_tasks.begin(), m_tasks.end());

    m_executor.start();
}




} // namespace threading

#endif // PERIODIC_EXECUTOR_HPP
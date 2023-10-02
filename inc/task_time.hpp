#ifndef TASK_TIME_HPP
#define TASK_TIME_HPP

#include "task.hpp"
#include <chrono>

namespace task {

template <typename Function, typename Clock>
class TaskTime : public Task{
public:
     TaskTime(Function func);
    ~TaskTime() noexcept = default;

    bool operator<(TaskTime const& a_other) const;

    bool run() override;
    void wake_up(); 
    void update_next_run(); 
    void update_next_run(std::chrono::duration<long long, std::nano> a_delay); 
    void update_period(std::chrono::duration<long long, std::nano> a_period);
    std::chrono::time_point<Clock> recive_next_run() const;

private:
    Function m_func;
    std::chrono::duration<long long, std::nano> m_period;
    std::chrono::time_point<Clock> m_next_run;

private:
    void sleep(const std::chrono::nanoseconds& a_duration);
};


template <typename Function, typename Clock>
TaskTime<Function, Clock>::TaskTime(Function a_func)
: m_func(a_func)
, m_period()
, m_next_run()
{
}

template <typename Function, typename Clock>
bool TaskTime<Function, Clock>::run()
{
    m_func();
    return true;
}

template <typename Function, typename Clock>
bool TaskTime<Function, Clock>::operator<(TaskTime const &a_other) const
{
    return m_next_run > a_other.m_next_run;
}

template <typename Function, typename Clock>
void TaskTime<Function, Clock>::wake_up() 
{
    auto now = Clock::now();
    auto sleep_duration = m_next_run - now;
    if (sleep_duration.count() > 0) {
        sleep(sleep_duration);
    }
}

template <typename Function, typename Clock>
void TaskTime<Function, Clock>::update_next_run()
{
    m_next_run = m_next_run + m_period;
}

template <typename Function, typename Clock>
void TaskTime<Function, Clock>::update_period(std::chrono::duration<long long, std::nano> a_period)
{
    m_period = a_period;
}

template <typename Function, typename Clock>
std::chrono::time_point<Clock> TaskTime<Function, Clock>::recive_next_run() const
{
    return m_next_run;
}

template <typename Function, typename Clock>
void TaskTime<Function, Clock>::update_next_run(std::chrono::duration<long long, std::nano> a_delay)
{
    m_next_run = a_delay + Clock::now();
}

template <typename Function, typename Clock>
void TaskTime<Function, Clock>::sleep(const std::chrono::nanoseconds& a_duration)
{
    auto start = Clock::now();
    while (Clock::now() - start < a_duration) {
    }
}

} // namespace task

#endif // TASK_TIME_HPP


#ifndef TASK_HPP
#define TASK_HPP

namespace task {

class Task {
public:
    virtual ~Task() noexcept = default;
    virtual void operator()() = 0;

protected:
    Task() = default;
    Task(Task const& a_other) = delete;
    Task& operator=(Task const& a_other) = delete;
};

}// namespace task

#endif // TASK_HPP
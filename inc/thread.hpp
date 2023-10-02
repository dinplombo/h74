#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>
#include <stdexcept>

namespace thread {

template<typename Function>
class Thread {
public:
    explicit Thread(Function func) noexcept;

    ~Thread() noexcept;
    Thread(Thread const& a_other) = delete;
    Thread& operator=(Thread const& a_other) = delete;

    void start();

private:
    Function m_func;
    pthread_t m_threadId;
};

template<typename Function>
Thread<Function>::Thread(Function a_func) noexcept
: m_func{a_func}
, m_threadId {}
{
}

template<typename Function>
Thread<Function>::~Thread() noexcept
{
    if (m_threadId != 0) {
        pthread_join(m_threadId, nullptr);
    }
}

namespace {
template <typename Function> 
void* thread_entry_point(void* a_func)
{
    Function* func = static_cast<Function*>(a_func);
    try{
        (*func)();
    } catch(...){
    }
    return nullptr;
}

} //

template <typename Function>
void Thread<Function>::start()
{
    if (pthread_create(&m_threadId, nullptr, thread_entry_point<Function>, &m_func) != 0){
        throw std::runtime_error("pthread_create fail");
    };
}

} // namespace thread

#endif // THREAD_HPP

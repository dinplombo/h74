#include "mu_test.h"
#include "thread_pool.hpp"

#include "task.hpp"

#include <memory> //unique_ptr make_unique
#include <thread> //sleepfor
#include <chrono> //seconds
#include <mutex> 
#include <atomic> 
#include <semaphore.h> 

using namespace concurrency;
using namespace task;

std::mutex mtx;

class Test1 : public Task {
public:
    explicit Test1(size_t a_test_number)
    : m_test_number{a_test_number}
    {
    }

    void operator()() override { 
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "test num:  " << m_test_number <<std::endl;
    }

private:
   size_t m_test_number;
};

class Test2 : public Task {
public:
    explicit Test2(size_t& a_counter)
    : m_counter{a_counter}
    {
    }

    void operator()() override {  
        std::unique_lock<std::mutex> lk(mtx);
        ++m_counter;
    }

private:
   size_t& m_counter;
};

class Test3 : public Task {
public:
    explicit Test3(sem_t& a_semaphore, size_t& a_counter)
    : m_semaphore{a_semaphore}
    , m_counter{a_counter}
    {
    }

    void operator()() override { 
        sem_post(&m_semaphore);
        std::unique_lock<std::mutex> lk(mtx);
        ++m_counter;
    }

private:
   sem_t& m_semaphore;
   size_t& m_counter;
};

class Test4 : public Task {
public:
    explicit Test4(std::atomic<int>& a_counter, int a_num_increment)
    : m_counter{a_counter}
    , m_num_increment{a_num_increment}
    {
    }

    void operator()() override {  
        for (int i = 0; i < m_num_increment; ++i){
            ++m_counter;
        }
    }

private:
    std::atomic<int>& m_counter;
    int m_num_increment;
};

BEGIN_TEST(shut_down_no_tasks)
    size_t counter = 0;
    size_t task_capacity = 10'000;;
    ThreadPool tp(3, task_capacity);
    tp.shutdown();

    ASSERT_THAT(counter == 0);
END_TEST

BEGIN_TEST(shut_down_with_tasks)
    sem_t s;
    sem_init(&s, 0, 0);
    size_t task_capacity = 10'000;
    ThreadPool tp(3, task_capacity);
    size_t counter = 0;

    for (size_t i = 0; i < task_capacity; ++i) {
        std::unique_ptr<Task> task = std::make_unique<Test3>(s, counter);
        tp.submit(std::move(task));
    }

    tp.shutdown();
    for (size_t i = 0; i < task_capacity; ++i) {
        sem_wait(&s);
    }

    sem_destroy(&s);
    ASSERT_THAT(counter == task_capacity);
END_TEST

BEGIN_TEST(add_after_shutdown)
    size_t counter = 0;
    std::mutex mtx;
    size_t task_capacity = 10'000;
    ThreadPool tp(3, task_capacity);
    for(size_t i = 0; i < task_capacity; ++i){
        std::unique_ptr<Task> task = std::make_unique<Test2>(counter);
        tp.submit(std::move(task));
        if(i == 2){
            tp.shutdown();
        }
    }
    ASSERT_THAT(counter == 3);
END_TEST

BEGIN_TEST(add_threads_worker)
    size_t counter = 0;
    std::mutex mtx;
    size_t task_capacity = 10'000;
    ThreadPool tp(3, task_capacity);
    for(size_t i = 0; i < task_capacity; ++i){
        std::unique_ptr<Task> task = std::make_unique<Test2>(counter);
        tp.submit(std::move(task));
    }
    tp.add(2);
    tp.shutdown();
    
    ASSERT_THAT(counter == task_capacity);
END_TEST

BEGIN_TEST(remove_threads)
    size_t counter = 0;
    size_t task_capacity = 10'000;
    ThreadPool tp(3, task_capacity);
    std::mutex mtx1;
    std::condition_variable cv;
    for(size_t i = 0; i < task_capacity; ++i){
        std::unique_ptr<Task> task = std::make_unique<Test2>(counter);
        tp.submit(std::move(task));
    }
    tp.remove(1);
    ASSERT_EQUAL(tp.threads() ,2);
    tp.shutdown();
    
    ASSERT_EQUAL(counter , task_capacity);
END_TEST

BEGIN_TEST(many_of_many)
    std::atomic<int> counter = 0;
    int task_capacity = 10'000;
    int num_increment = 5'000;
    ThreadPool tp(3, task_capacity);
    for(int i = 0; i < task_capacity; ++i){
        std::unique_ptr<Task> task = std::make_unique<Test4>(counter, num_increment);
        tp.submit(std::move(task));
    }

    tp.shutdown();
    ASSERT_THAT(counter == task_capacity * num_increment);
END_TEST

BEGIN_TEST(shutddown_immediate)
    size_t counter = 0;
    std::mutex mtx;
    size_t task_capacity = 10'000;
    ThreadPool tp(3, task_capacity);

    for(size_t i = 0; i < task_capacity; ++i){
        std::unique_ptr<Task> task = std::make_unique<Test2>(counter);
        tp.submit(std::move(task));
    }
    tp.shutdown_immediate();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    ASSERT_THAT(counter < task_capacity);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(shut_down_no_tasks)
    TEST(shut_down_with_tasks)
    TEST(add_after_shutdown)
    TEST(add_threads_worker)
    TEST(remove_threads)
    TEST(many_of_many)
    TEST(shutddown_immediate)

END_SUITE

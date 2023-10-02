#include "mu_test.h"
#include "thread.hpp"
#include "preiodic_executor.hpp"
#include "task_time.hpp"

#include <iostream>
#include <unistd.h>
#include <exception>
#include <functional>
#include <chrono>

using namespace thread;
using namespace task;
using namespace threading;


// namespace{

struct MyFunctionObject {
    void operator()()
    {
        for (int i = 0; i < 3; ++i) {
            std::cout << "hellow in thread object function" << '\n';
            sleep(2);
        }
    } 
};

void func()
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "hellow in thread ptr function" << '\n';
        sleep(1);
    }
}

void task_func_a()
{
    static int count = 0;
    std::cout << "Executing task a " << count++ << std::endl;
}

void task_func_b()
{
    static int count = 0;
    std::cout << "Executing task b " << count++ << std::endl;
}

void task_func_c()
{
    static int count = 0;
    std::cout << "Executing task c " << count++ << std::endl;
}

template<typename Func>
class CountedTask : public Task {
public:
    CountedTask(int a_count, const char* a_name, Func a_function)
    : m_count{a_count}
    , m_name{a_name}
    , m_func{a_function}
    {}

    bool run() noexcept override {  
        std::cout << "task " << m_name << ": " << m_count << std::endl;
        m_func();
        --m_count;
        return m_count > 0;
    }

private:
    int m_count;
    const char* m_name;
    Func m_func;

};

template<typename Func>
Task* make_task(int a_count, const char* a_name, Func a_function)
{
    return new CountedTask(a_count, a_name, a_function);
}
// } //namespace


BEGIN_TEST(object_function)
    thread::Thread<MyFunctionObject> myThread(MyFunctionObject{});
    try{
        myThread.start();
    } catch (std::exception const& result){
        std::cout << result.what() << '\n';
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(throw_exeception)
    int num = 2;
    thread::Thread myThread([num](){throw 1;});
    myThread.start();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(lambda_func)
    int num = 2;
    thread::Thread myThread([num](){std::cout << "hellow in thread lambda" << "num is: " << num << '\n';});
    myThread.start();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(ptr_function)
    thread::Thread myThread(func);
    try{
        myThread.start();
    } catch (std::exception const& result){
        std::cout << result.what() << '\n';
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(ptr_and_objet_function)
    thread::Thread ptr_thread(func);
    thread::Thread<MyFunctionObject> obj_thread(MyFunctionObject{});
    try{
        ptr_thread.start();
        obj_thread.start();
    } catch (std::exception const& result){
        std::cout << result.what() << '\n';
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(periodic_executor_test)
    PeriodicExecutor<std::chrono::steady_clock> executor;
    Task* task1 = new TaskTime<std::function<void()>, std::chrono::steady_clock>(task_func_a);
    Task* task2 = new TaskTime<std::function<void()>, std::chrono::steady_clock>(task_func_b);
    Task* task3 = new TaskTime<std::function<void()>, std::chrono::steady_clock>(task_func_c);

    executor.add(*task1, 0, 10);
    executor.add(*task2, 0, 13);
    executor.add(*task3, 0, 5);

    executor.start();

    ASSERT_PASS();
END_TEST

BEGIN_TEST(periodic_executor_mul_test)
    PeriodicExecutor<std::chrono::steady_clock> executor;
    executor.add(*make_task(1, "lasttask", [](){std::cout << "!!!!\n";}), 300, 0);
    executor.add(*make_task(10, "10task", [](){std::cout << "####\n";}), 0, 8);
    executor.add(*make_task(15, "15task", [](){std::cout << "$$$$\n";}), 10, 5);
    executor.add(*make_task(18, "18task", [](){std::cout << "%%%%\n";}), 7, 9);
    executor.add(*make_task(13, "13task", [](){std::cout << "^^^^\n";}), 20, 2);

    executor.start();

    ASSERT_PASS();
END_TEST

BEGIN_TEST(periodic_test)
    PeriodicExecutor<std::chrono::steady_clock> executor;
    executor.start();

    ASSERT_PASS();
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    IGNORE_TEST(periodic_executor_test)
    TEST(periodic_executor_mul_test)
    TEST(throw_exeception)
    TEST(object_function)
    TEST(lambda_func)
    TEST(ptr_function)
    TEST(ptr_and_objet_function)
    TEST(periodic_test)
        
    
END_SUITE
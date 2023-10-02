#include "mu_test.h"
#include "blocking_queue.hpp"

#include <thread>

using namespace ds_thread_safe;

BEGIN_TEST(init_class)
    BlockingQueue<int> bq(100);
    
    ASSERT_EQUAL(bq.capacity(), 100);
END_TEST

BEGIN_TEST(enqeue)
    BlockingQueue<int> bq(100);
    bq.enqueue(3);
    
    ASSERT_EQUAL(bq.size(), 1);
END_TEST

BEGIN_TEST(deqeue)
    BlockingQueue<int> bq(100);
    bq.enqueue(3);
    int first_queue;
    bq.dequeue(first_queue);
    
    ASSERT_EQUAL(bq.size(), 0);
    ASSERT_EQUAL(first_queue, 3);
END_TEST

BEGIN_TEST(full)
    BlockingQueue<int> bq(1);
    bq.enqueue(3);
    
    ASSERT_THAT(bq.full());
END_TEST

BEGIN_TEST(empty)
    BlockingQueue<int> bq(100);
    bq.enqueue(3);
    int first_queue;
    bq.dequeue(first_queue);
    
    ASSERT_THAT(bq.empty());
END_TEST

BEGIN_TEST(thread_enqueue_dequeue)
    BlockingQueue<int> bq(1000);
    std::vector<std::thread> tasks;
    size_t num_thread = 20;
	tasks.reserve(num_thread);
    int first_queue;
    for(size_t i = 0; i < num_thread / 2; ++i){
		std::thread t_en([&bq](int a){bq.enqueue(a);}, 4);
		std::thread t_de([&bq, &first_queue](){bq.dequeue(first_queue);});
		tasks.push_back(std::move(t_en));
		tasks.push_back(std::move(t_de));
	}

    for (auto& t : tasks){
       t.join();
    }
    
    ASSERT_EQUAL(bq.size(), 0);
END_TEST



TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(init_class)
    TEST(enqeue)
    TEST(deqeue)
    TEST(full)
    TEST(empty)
    TEST(thread_enqueue_dequeue)

END_SUITE

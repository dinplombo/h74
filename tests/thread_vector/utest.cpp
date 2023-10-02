#include "mu_test.h"
#include "thread_vector.hpp"

#include <chrono>

using namespace thread;

BEGIN_TEST(three_thread)
    std::vector<int> random_vector;
    init_random_vector(random_vector);

    auto start_time3 = std::chrono::high_resolution_clock::now();
    thread_counter(random_vector, 3);
    auto end_time3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time3- start_time3);
    std::cout << "Time taken for thread_counter(random_vector, 3): " << duration3.count() << " ms\n";
    ASSERT_PASS();
END_TEST

BEGIN_TEST(one_thread)
    std::vector<int> random_vector;
    init_random_vector(random_vector);

    auto start_time1 = std::chrono::high_resolution_clock::now();
    thread_counter(random_vector, 1);
    auto end_time1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - start_time1);
    std::cout << "Time taken for thread_counter(random_vector, 1): " << duration1.count() << " ms\n";
    ASSERT_PASS();
END_TEST

BEGIN_TEST(two_thread)
    std::vector<int> random_vector;
    init_random_vector(random_vector);

    auto start_time2 = std::chrono::high_resolution_clock::now();
    thread_counter(random_vector, 2);
    auto end_time2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - start_time2);
    std::cout << "Time taken for thread_counter(random_vector, 2): " << duration2.count() << " ms\n";
    ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(three_thread)
    TEST(one_thread)
    TEST(two_thread)
	
END_SUITE






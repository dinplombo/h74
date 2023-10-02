#include "mu_test.h"
#include "queue_stack.hpp"

BEGIN_TEST(push)
    ds::QueueStack s1(10);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    ASSERT_EQUAL(s1.size(),4);
END_TEST

BEGIN_TEST(push_2)
    ds::QueueStack s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    ASSERT_EQUAL(s1.size(),4);
END_TEST


BEGIN_TEST(pop)
    ds::QueueStack s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    int value;
    s1.pop(value);
    ASSERT_EQUAL(value,1);
END_TEST

BEGIN_TEST(pop_2)
    ds::QueueStack s1(10);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    int value;
    s1.pop(value);
    s1.push(5);
    s1.pop(value);
    ASSERT_EQUAL(value,2);
END_TEST

BEGIN_TEST(is_empty)
    ds::QueueStack s1(10);
    s1.push(1);
    s1.push(2);
    int value;
    s1.pop(value);
    s1.pop(value);
    ASSERT_EQUAL(s1.is_empty(), true);
END_TEST

BEGIN_TEST(is_empty_2)
    ds::QueueStack s1(10);
    s1.push(1);
    s1.push(2);
    int value;
    s1.pop(value);
    ASSERT_EQUAL(s1.is_empty(), false);
END_TEST

BEGIN_TEST(is_full)// fill 2 in stack->darin to pop stack->try to fill more then 2 again
    ds::QueueStack s1(2);
    for (size_t i = 1; i < 5; ++i){
        s1.push(i);
    }
    ASSERT_EQUAL(s1.is_full(), true);
END_TEST

BEGIN_TEST(is_full_2)
    ds::QueueStack s1(2);
    s1.push(1);
    s1.push(2);
    int value;
    s1.pop(value);
    s1.push(3);
    s1.push(4);
    ASSERT_EQUAL(s1.is_full(), true);
END_TEST

BEGIN_TEST(is_full_3)
    ds::QueueStack s1(3);
    s1.push(1);
    s1.push(2);
    int value;
    s1.pop(value);
    s1.push(2);
    ASSERT_EQUAL(s1.is_full(), false);
END_TEST

BEGIN_TEST(memory_leak_and_double_free)
    ds::QueueStack s1(10);
    s1.push(4);
    ds::QueueStack t(100);
    t = s1; 

    ASSERT_EQUAL(s1.size(), t.size());
    ASSERT_EQUAL(s1.capacity(), t.capacity());
END_TEST




TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(push)
    TEST(push_2)
    TEST(pop)
    TEST(pop_2)
    TEST(is_empty)
    TEST(is_empty_2)
    TEST(is_full)
    TEST(is_full_2)
    TEST(is_full_3)
    TEST(memory_leak_and_double_free)
    
	
END_SUITE
#include "mu_test.h"
#include "stack.hpp"

BEGIN_TEST(init_class)
    ds::Stack s1(100);
    
    ASSERT_EQUAL(s1.capacity(), 100);
    ASSERT_NOT_EQUAL(s1.data_array(), 0);
END_TEST

BEGIN_TEST(size)
    ds::Stack s1(100);
    ASSERT_EQUAL(s1.size(), 0);
    s1.push(4);
    ASSERT_EQUAL(s1.size(), 1);
END_TEST

BEGIN_TEST(push)
    ds::Stack s1(100);
    s1.push(4).push(5);
    ASSERT_EQUAL(s1.size(), 2);
END_TEST

BEGIN_TEST(over_flaw)
    ds::Stack s1(100);
    for(size_t i = 0; i <= 100; ++i){
        s1.push(4);
    }
    ASSERT_EQUAL(s1.size(), 101);
END_TEST

BEGIN_TEST(pop)
    ds::Stack s1(100);
    int a;
    s1.push(4).pop(a);
    ASSERT_EQUAL(a, 4);
END_TEST

BEGIN_TEST(under_flaw)
    ds::Stack s1(100);
    int a;
    s1.pop(a);
    ASSERT_EQUAL(a, 0);
END_TEST

BEGIN_TEST(is_empty)
    ds::Stack s1(100);
    ASSERT_EQUAL(s1.is_empty(), true);
END_TEST

BEGIN_TEST(is_not_empty)
    ds::Stack s1(100);
    s1.push(4);
    ASSERT_EQUAL(s1.is_empty(), false);
END_TEST

BEGIN_TEST(is_full)
    ds::Stack s1(100);
    for(size_t i = 0; i < 100; ++i){
        s1.push(4);
    }
    ASSERT_EQUAL(s1.is_full(), true);
END_TEST

BEGIN_TEST(is_not_full)
    ds::Stack s1(100);
    s1.push(4);
    ASSERT_EQUAL(s1.is_full(), false);
END_TEST

BEGIN_TEST(print)
    ds::Stack s1(100);
    for(size_t i = 0; i < 100; ++i){
        s1.push(i);
    }
    s1.print();
END_TEST

BEGIN_TEST(drain)
    ds::Stack s1(20);
    ds::Stack s2(10);
    for(size_t i = 0; i < 5; ++i){
        s1.push(i);
        s2.push(10 - i);
    }
    ds::drain(s1,s2);
    int a;
    ASSERT_EQUAL(s1.size(), 10);
    s1.pop(a);
    ASSERT_EQUAL(a, 10);
END_TEST

BEGIN_TEST(add)
    ds::Stack s1(10);
    ds::Stack s2(10);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s2.push(31);
    s2.push(32);
    s2.push(33);
    s1 += s2;
    int a;
    ASSERT_EQUAL(s1.size(), 6);
    s1.pop(a);
    ASSERT_EQUAL(a, 33);
    ASSERT_EQUAL(s2.is_empty(), true);
END_TEST

BEGIN_TEST(equal)
    ds::Stack s1(10);
    s1.push(4);
    ds::Stack t = s1;

    ASSERT_EQUAL(s1.size(), t.size());
    ASSERT_EQUAL(s1.capacity(), t.capacity());
END_TEST

BEGIN_TEST(memory_leak)
    ds::Stack s1(10);
    s1.push(4);
    ds::Stack t(100);
    t = s1; 

    ASSERT_EQUAL(s1.size(), t.size());
    ASSERT_EQUAL(s1.capacity(), t.capacity());
END_TEST

BEGIN_TEST(not_equal)
    ds::Stack s1(10);
    s1.push(4);
    ds::Stack t(100);
    t = s1; 
    t.push(2);
    ASSERT_NOT_EQUAL(s1.size(), t.size());
END_TEST

BEGIN_TEST(not_equal_2)
    ds::Stack s1(10);
    s1.push(4);
    ds::Stack t = s1;
    s1.push(2);
    ASSERT_NOT_EQUAL(s1.size(), t.size());
END_TEST

BEGIN_TEST(peek)
    ds::Stack s1(10);
    s1.push(4);
    s1.push(2);
    int a;
    s1.peek(a);
    ASSERT_EQUAL(a, 2);
END_TEST

BEGIN_TEST(self_assignment)
    ds::Stack s1(10);
    s1.push(4);
    s1 = s1;
    int value;
    s1.pop(value);
    ASSERT_EQUAL(value,4);
END_TEST

BEGIN_TEST(swap)
    ds::Stack s1(10);
    s1.push(4);
    ds::Stack s2(10);
    s1.swap(s2);
    ASSERT_EQUAL(s1.size(),0);
    ASSERT_EQUAL(s2.size(),1);
END_TEST

BEGIN_TEST(move_cctor)
    ds::Stack s1(10);
    s1.push(4);
    ds::Stack s2(std::move(s1));
    ASSERT_EQUAL(s1.size(),0);
    ASSERT_EQUAL(s2.size(),1);
END_TEST

BEGIN_TEST(move_assign)
    ds::Stack s1(10);
    ds::Stack s2(10);
    s1.push(4);
    s2 = std::move(s1);
    ASSERT_EQUAL(s2.size(),1);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    IGNORE_TEST(memory_leak)
	TEST(init_class)
    TEST(size)
    TEST(push)
    IGNORE_TEST(over_flaw)
    TEST(pop)
    IGNORE_TEST(under_flaw)
    TEST(is_empty)
    TEST(is_not_empty)
    TEST(is_full)
    TEST(is_not_full)
    IGNORE_TEST(print)
    TEST(drain)
    TEST(add)
    TEST(equal)
    TEST(not_equal)
    TEST(not_equal_2)
    TEST(peek)
    TEST(self_assignment)
    TEST(swap)
    TEST(move_cctor)
    TEST(move_assign)
	
END_SUITE

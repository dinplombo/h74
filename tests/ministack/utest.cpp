#include "mu_test.h"
#include "ministack.hpp"


BEGIN_TEST(push)
    ds::Ministack s1(10);
    s1.push(2);
    s1.push(4);
    s1.push(1);
    s1.push(3);
    ASSERT_EQUAL(s1.size(),4);
END_TEST

BEGIN_TEST(min)
    ds::Ministack s1(10);
    s1.push(2);
    s1.push(4);
    s1.push(1);
    s1.push(3);
    ASSERT_EQUAL(s1.min(),1);
END_TEST

BEGIN_TEST(pop)
    ds::Ministack s1(10);
    s1.push(2);
    s1.push(4);
    s1.push(1);
    s1.push(3);
    ASSERT_EQUAL(s1.pop(),3);
END_TEST

BEGIN_TEST(min_2)
    ds::Ministack s1(10);
    s1.push(2);
    s1.push(4);
    s1.push(1);
    s1.push(3);
    s1.pop();
    s1.pop();
    ASSERT_EQUAL(s1.min(),2);
END_TEST

BEGIN_TEST(min_3)
    ds::Ministack s1(10);
    s1.push(2);
    s1.push(4);
    s1.push(1);
    s1.push(3);
    ds::Ministack t = s1;
    s1.pop();
    s1.pop();
    ASSERT_EQUAL(s1.min(), 2);
    ASSERT_EQUAL(t.min(), 1);
END_TEST

BEGIN_TEST(equal)
    ds::Ministack s1(10);
    s1.push(2);
    ds::Ministack t = s1;
    ASSERT_EQUAL(s1.size(), t.size());
END_TEST

BEGIN_TEST(memory_leak)
    ds::Ministack s1(10);
    s1.push(4);
    ds::Ministack t(100);
    t = s1; 

    ASSERT_EQUAL(s1.size(), t.size());
    ASSERT_EQUAL(s1.capacity(), t.capacity());
END_TEST

BEGIN_TEST(not_equal)
    ds::Ministack s1(10);
    s1.push(4);
    ds::Ministack t(100);
    t = s1; 
    t.push(2);
    ASSERT_NOT_EQUAL(s1.size(), t.size());
    ASSERT_EQUAL(s1.capacity(), t.capacity());
END_TEST

BEGIN_TEST(not_over_flaw)
    ds::Ministack s1(10);
    ds::Ministack t(10);
    for(size_t i = 0; i < 10; ++i){
        s1.push(i);
        t.push(10-i);
    }
    s1.pop();
    t = s1; 
    t.push(2);
    ASSERT_EQUAL(t.size(), 10);
    ASSERT_EQUAL(s1.size(), 9);
END_TEST

BEGIN_TEST(will_fail_under_flaw)
    ds::Ministack s1(10);
    ds::Ministack t(10);
    t.push(1);
    t.push(2);
    t = s1; 
    t.pop();
    ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(push)
    TEST(min)
    TEST(pop)
    TEST(min_2)
    TEST(memory_leak)
    TEST(not_equal)
    TEST(not_over_flaw)
    IGNORE_TEST(will_fail_under_flaw)
    TEST(min_3)
    TEST(equal)
    
    
	
END_SUITE
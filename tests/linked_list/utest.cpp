#include "mu_test.h"
#include "linked_list.hpp"
#include <iostream>


BEGIN_TEST(init)
    ds::Linked_list<int> l1;

    
    ASSERT_PASS();
END_TEST

BEGIN_TEST(push_head)
    ds::Linked_list<int> l1;
    int value = 3;
    l1.push_head(value);

    ASSERT_EQUAL(l1.size(),1);
END_TEST

BEGIN_TEST(push_tail)
    ds::Linked_list<int> l1;
    int value = 3;
    l1.push_tail(value);
    
    ASSERT_EQUAL(l1.size(),1);
END_TEST

BEGIN_TEST(pop_head)
    ds::Linked_list<int> l1;
    int value = 3;
    l1.push_tail(value);
    int returned;
    l1.pop_head(returned);
    
    ASSERT_EQUAL(returned,3);
END_TEST

BEGIN_TEST(pop_tail)
    ds::Linked_list<int> l1;
    int value = 3;
    l1.push_tail(value);
    int returned;
    l1.pop_tail(returned);
    
    ASSERT_EQUAL(returned,3);
END_TEST

BEGIN_TEST(insert_after)
    ds::Linked_list<int> l1;
    l1.push_head(3);
    l1.push_head(9);
    l1.insert_after(9,6);
    int returned;
    l1.pop_tail(returned);

    ASSERT_EQUAL(returned,3);
END_TEST

BEGIN_TEST(clear)
    ds::Linked_list<int> l1;
    l1.push_head(3);
    l1.push_head(9);
    l1.insert_after(9,6);
    ASSERT_EQUAL(l1.size(),3);
    l1.clear();

    ASSERT_EQUAL(l1.size(),0);
END_TEST

BEGIN_TEST(swap)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l2.push_head(9);
    ASSERT_EQUAL(l1.size(),2);
    ASSERT_EQUAL(l2.size(),1);
    l1.swap(l2);

    ASSERT_EQUAL(l1.size(),1);
    ASSERT_EQUAL(l2.size(),2);
END_TEST

BEGIN_TEST(swap_2)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l2.push_head(9);
    l1.swap(l2);
    int returend1;
    l1.pop_head(returend1);
    int returend2;
    l2.pop_head(returend2);

    ASSERT_EQUAL(returend1,9);
    ASSERT_EQUAL(returend2,6);
END_TEST

BEGIN_TEST(remove_function)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l1.remove(3);
    int returend1;
    l1.pop_tail(returend1);

    ASSERT_EQUAL(returend1,6);
    ASSERT_EQUAL(l1.size(),1);
END_TEST

BEGIN_TEST(contians)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);

    ASSERT_THAT(l1.contains(6));
END_TEST

BEGIN_TEST(not_contians)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);

    ASSERT_FAIL(l1.contains(8));
END_TEST

BEGIN_TEST(equal)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l2.push_head(3);
    l2.push_head(6);
    l2.push_head(9);

    ASSERT_THAT(l1 == l2);
END_TEST

BEGIN_TEST(not_equal)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l2.push_head(3);
    l2.push_head(6);
    l2.push_head(4);

    ASSERT_THAT(l1 != l2);
END_TEST

BEGIN_TEST(smaller)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l2.push_head(3);
    l2.push_head(6);
    l2.push_head(9);

    ASSERT_FAIL(l1 < l2);
END_TEST

BEGIN_TEST(smaller_2)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l2.push_head(3);
    l2.push_head(6);
    l2.push_head(12);

    ASSERT_THAT(l1 < l2);
END_TEST

BEGIN_TEST(reverse)
    ds::Linked_list<int> l1;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l1.reverse();
    int returend;
    l1.pop_head(returend);
    ASSERT_EQUAL(returend,3);
END_TEST

int print_list(int& a_value, int& a_context)
{
    a_context = 1;
    std::cout << a_value << " ";
    return 1;
}

BEGIN_TEST(for_each)
    ds::Linked_list<int> l1;

    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    int dummy = 0;
    std::cout << "Printing the list: ";
    l1.for_each(print_list, dummy);
    std::cout << '\n';

    ASSERT_PASS();
END_TEST

BEGIN_TEST(sum)
    ds::Linked_list<double> l1;
    l1.push_head(3.1);
    l1.push_head(6.1);
    l1.push_head(9.1);
    double sum = 0;
    sum = l1.sum(sum);

    ASSERT_EQUAL(sum, 18.3);
END_TEST

BEGIN_TEST(op_equal)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l2 = l1;
    int dummy = 0;
    std::cout << "Printing the list: ";
    l1.for_each(print_list, dummy);
    std::cout << '\n';


    ASSERT_EQUAL(l1.size(), l2.size());
END_TEST

BEGIN_TEST(splice)
    ds::Linked_list<int> l1;
    ds::Linked_list<int> l2;
    ds::Linked_list<int> l3;
    l1.push_head(3);
    l1.push_head(6);
    l1.push_head(9);
    l2.push_head(1);
    l2.push_head(2);
    l2.push_head(3);
    l3 = splice(l1, l2);

    ASSERT_EQUAL(l3.size(), 6);
END_TEST





TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(init)
    TEST(push_head)
    TEST(push_tail)
    TEST(pop_head)
    TEST(pop_tail)
    TEST(insert_after)
    TEST(clear)
    TEST(swap)
    TEST(swap_2)
    TEST(remove_function)
    TEST(contians)
    TEST(not_contians)
    TEST(equal)
    TEST(not_equal)
    TEST(smaller)
    TEST(smaller_2)
    TEST(reverse)
    TEST(for_each)
    TEST(sum)
    TEST(op_equal)
    TEST(splice)
	
END_SUITE
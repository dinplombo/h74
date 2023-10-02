
#include "mu_test.h"
#include "rational.hpp"

BEGIN_TEST(init_class)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n1);
    algebra::Rational r3;

	ASSERT_EQUAL(r1.value(), 0.5);
	ASSERT_EQUAL(r2.value(), 20);
    ASSERT_EQUAL(r3.value(), 0);
END_TEST

BEGIN_TEST(inverse_1)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    r1.inverse();

	ASSERT_THAT(r1.value() ==  2);
END_TEST

BEGIN_TEST(inverse_2)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(1, 2);
    r1.inverse().inverse(); 

	ASSERT_THAT(r1.value() == r2.value());
END_TEST

BEGIN_TEST(add)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational const r1(n1, n2);
    algebra::Rational const r2(n2, n1);
    algebra::Rational r3(5, 2);
    algebra::Rational r4 = r1 + r2;

	ASSERT_THAT(r3.value() == r4.value());
END_TEST

BEGIN_TEST(multiply)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);
    algebra::Rational r3 = r1*(r2);

	ASSERT_THAT(r3.value() == 1);
END_TEST

BEGIN_TEST(sub)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);
    algebra::Rational r3 = r1 - (r2);
    algebra::Rational r4(-3, 2);

	ASSERT_THAT(r3.value() == r4.value());
END_TEST

BEGIN_TEST(dev)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);
    algebra::Rational r3 = r1 / (r2);
    algebra::Rational r4(1, 4);

	ASSERT_THAT(r3.value() == r4.value());
END_TEST

BEGIN_TEST(pre_increment)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r3 = ++r1;
    algebra::Rational r4(3, 2);

	ASSERT_THAT(r3.value() == r4.value());
END_TEST

BEGIN_TEST(post_increment)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r3 = r1++;
    algebra::Rational r4(1, 2);
    algebra::Rational r5(3, 2);

	ASSERT_THAT(r3.value() == r4.value());
    ASSERT_THAT(r1.value() == r5.value());
END_TEST

BEGIN_TEST(pre_decrement)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r3 = --r1;
    algebra::Rational r4(-1, 2);

	ASSERT_THAT(r3 == r4);
END_TEST

BEGIN_TEST(post_decrement)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r3 = r1--;

	ASSERT_EQUAL(r3.value(), 0.5);
    ASSERT_EQUAL(r1.value(), -0.5);
END_TEST

BEGIN_TEST(less)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);

	ASSERT_THAT(r1 < r2);
END_TEST

BEGIN_TEST(not_equal)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);

	ASSERT_THAT(r1 != r2);
END_TEST

BEGIN_TEST(equal)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1*4);

	ASSERT_THAT(r1 == r2);
END_TEST

BEGIN_TEST(bigger)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);

	ASSERT_THAT(r2 > r1);
END_TEST

BEGIN_TEST(bigger_and_equal)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);

	ASSERT_THAT(r2 >= r1);
    ASSERT_THAT(r2.value() >= 2);
END_TEST

BEGIN_TEST(less_and_equal)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);

	ASSERT_THAT(r1 <= r2);
    ASSERT_THAT(r2.value() <= 2);
END_TEST

BEGIN_TEST(sum_legit)
	int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);
    algebra::Rational r_arrary[] = {r1,r1,r1,r2};

	ASSERT_EQUAL(sum(r_arrary,4).value(), 3.5);
END_TEST

BEGIN_TEST(sum_array_null)

	ASSERT_EQUAL(algebra::sum(NULL,4).value(), 0);
END_TEST

BEGIN_TEST(sumd_legit)
    int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2, n1);
    algebra::Rational r_arrary[] = {r1,r1,r1,r2};

	ASSERT_EQUAL(sumd(r_arrary,4), 3.5);
END_TEST

BEGIN_TEST(swap)
    int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2*2, n1);
    r1.swap(r2);
	ASSERT_EQUAL(r1.value(), 4);
    ASSERT_EQUAL(r2.value(), 0.5);
END_TEST

BEGIN_TEST(swap_between_two)
    int n1 = 20;
    int n2 = 40;
    algebra::Rational r1(n1, n2);
    algebra::Rational r2(n2*2, n1);
    algebra::swap(r1, r2);

	ASSERT_EQUAL(r2.value(), 0.5);
    ASSERT_EQUAL(r1.value(), 4);
END_TEST



TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(init_class)
    TEST(inverse_1)
    TEST(inverse_2)
    TEST(add)
    TEST(multiply)
    TEST(sub)
    TEST(dev)
    TEST(pre_increment)
    TEST(post_increment)
    TEST(pre_decrement)
    TEST(post_decrement)
    TEST(less)
    TEST(not_equal)
    TEST(equal)
    TEST(bigger)
    TEST(bigger_and_equal)
    TEST(less_and_equal)
    TEST(sum_legit)
    TEST(sum_array_null)
    TEST(sumd_legit)
    TEST(swap)
    TEST(swap_between_two)
	
END_SUITE






// void test_swap_between(int& test_count, int& success_count)
// {
//     int n1 = 20;
//     int n2 = 40;
//     algebra::Rational r1(n1, n2);
//     algebra::Rational r2(n2*2, n1);
//     test_count += 1;
//     algebra::swap(r1, r2);
//     if (r1.value() == 4 && r2.value() == 0.5) {
//         printf("%-25s%s\n", "Test swap_between", "\x1B[32mPASSED\x1B[37m");
//         success_count += 1;
//     }
//     else{
//         printf("%-25s%s\n", "Test swap_between", "\x1B[31mFAILED!\x1B[37m\n");
//     }
// }

// int main()
// {
//     int test_count = 0;
//     int success_count = 0;
//     test_init(test_count, success_count);//can move &success_count
//     test_inverse_1(test_count, success_count);
//     test_inverse_2(test_count, success_count);
//     test_add(test_count, success_count);
//     test_multiply(test_count, success_count);
//     test_dev(test_count, success_count);
//     test_sub(test_count, success_count);
//     test_increment_pre(test_count, success_count);
//     test_increment_post(test_count, success_count);
//     test_decrement_pre(test_count, success_count);
//     test_decrement_post(test_count, success_count);
//     test_less(test_count, success_count);
//     test_equal(test_count, success_count);
//     test_not_equal(test_count, success_count);
//     test_bigger(test_count, success_count);
//     test_bigger_and_equal(test_count, success_count);
//     test_less_and_equal(test_count, success_count);
//     test_sum_legit(test_count, success_count);
//     test_sum_array_null(test_count, success_count);
//     test_sumd_legit(test_count, success_count);
//     test_swap(test_count, success_count);
//     test_swap_between(test_count, success_count);
//     printf("total test --->\x1B[34m%d\x1B[37m<--- \ntotal_pass --->\x1B[34m%d\x1B[37m<--- \n", test_count, success_count);

//     return 1;
    
// } 
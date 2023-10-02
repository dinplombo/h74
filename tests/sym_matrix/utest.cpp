#include "mu_test.h"
#include "sym_matrix.hpp"
#include <iostream>


BEGIN_TEST(init)
    ds::SymMatrix<int> metrix(3);

    
    ASSERT_PASS();
END_TEST

BEGIN_TEST(add_num)
    ds::SymMatrix<int> metrix(3);
    metrix(0,1) = 4;

    ASSERT_EQUAL(metrix(0,1), 4);
END_TEST

BEGIN_TEST(add_num_1)
    ds::SymMatrix<int> metrix(3);
    metrix(0,1) = 4;
    metrix(2,0) = 5;

    ASSERT_EQUAL(metrix(0,2), 5);
    ASSERT_EQUAL(metrix(0,2), metrix(2,0));
END_TEST

BEGIN_TEST(cctor)
    ds::SymMatrix<int> f_matrix(3);
    f_matrix(0,1) = 4;
    f_matrix(2,0) = 5;
    ds::SymMatrix<int> s_matrix = f_matrix;

    ASSERT_EQUAL(s_matrix(0,2), 5);
END_TEST

BEGIN_TEST(cctor_long)
    ds::SymMatrix<int> f_matrix(3);
    f_matrix(0,1) = 4;
    f_matrix(2,0) = 5;
    ds::SymMatrix<int> s_matrix = f_matrix;
    s_matrix += f_matrix; //s_matrix ->(0,1)= 8 ; (0,2) = 10
    ds::SymMatrix<long> t_matrix = f_matrix; //t_matrix ->(0,1)= 4 ; (0,2) = 5
    t_matrix += s_matrix; //t_matrix ->(0,1)= 12 ; (0,2) = 15

    ASSERT_EQUAL(t_matrix(0,2), 15);
END_TEST

BEGIN_TEST(op_equal_long_int)
    ds::SymMatrix<int> f_matrix(3);
    f_matrix(0,1) = 4;
    f_matrix(2,0) = 5;
    ds::SymMatrix<int> s_matrix = f_matrix;
    s_matrix += f_matrix; //s_matrix ->(0,1)= 8 ; (0,2) = 10
    ds::SymMatrix<long> t_matrix(3);
    t_matrix = s_matrix;

    ASSERT_EQUAL(t_matrix(0,2), 10);
END_TEST

BEGIN_TEST(equal_op)
    ds::SymMatrix<int> f_matrix(3);
    ds::SymMatrix<int> s_matrix(3);
    f_matrix(0,1) = 4;
    f_matrix(2,0) = 5;
    s_matrix(0,1) = 6;
    s_matrix(2,0) = 7;
    ASSERT_EQUAL(s_matrix(0,1), 6);
    s_matrix = f_matrix;

    ASSERT_EQUAL(s_matrix(0,1), 4);
END_TEST

BEGIN_TEST(add_equal_op)
    ds::SymMatrix<int> f_matrix(3);
    ds::SymMatrix<int> s_matrix(3);
    f_matrix(0,0) = 4;
    f_matrix(0,1) = 5;
    s_matrix(0,2) = 6;
    s_matrix(1,1) = 7;
    s_matrix += f_matrix;

    ASSERT_EQUAL(s_matrix(0,0), 4);
    ASSERT_EQUAL(s_matrix(1,1), 7);
END_TEST

BEGIN_TEST(add_op)
    ds::SymMatrix<int> f_matrix(3);
    ds::SymMatrix<int> s_matrix(3);
    ds::SymMatrix<int> t_matrix(4);
    f_matrix(0,0) = 4;
    f_matrix(0,1) = 5;
    s_matrix(0,2) = 6;
    s_matrix(1,1) = 7;
    t_matrix = s_matrix + f_matrix;

    ASSERT_EQUAL(t_matrix(0,0), 4);
    ASSERT_EQUAL(t_matrix(1,1), 7);
END_TEST

BEGIN_TEST(self_assignment)
    ds::SymMatrix<int> f_matrix(3);
    f_matrix(1,1) = 7;
    f_matrix = f_matrix;

    ASSERT_EQUAL(f_matrix(1,1), 7);
END_TEST

BEGIN_TEST(op_add_long_int)
    ds::SymMatrix<int> f_matrix(3);
    f_matrix(0,1) = 4;
    f_matrix(2,0) = 5;
    ds::SymMatrix<long> s_matrix(3);
    s_matrix(0,1) = 4;
    s_matrix(2,0) = 5;
    ds::SymMatrix<long> t_matrix(3);
    t_matrix = f_matrix + s_matrix;

    ASSERT_EQUAL(t_matrix(0,2), 10);
END_TEST

BEGIN_TEST(op_add_equal_long_int)
    ds::SymMatrix<int> f_matrix(3);
    f_matrix(0,1) = 4;
    f_matrix(2,0) = 5;
    ds::SymMatrix<long> s_matrix(3);
    s_matrix(0,1) = 4;
    s_matrix(2,0) = 5;
    f_matrix = f_matrix + s_matrix;

    ASSERT_EQUAL(f_matrix(0,2), 10);
END_TEST


BEGIN_TEST(op_cout)
    ds::SymMatrix<int> f_matrix(3);
    for (size_t i = 0; i < 3; ++i){
        for (size_t j = 0; j + i < 3; ++j){
            f_matrix(i,j + i) = 6;
        }
    }
    std::cout << f_matrix;
    ASSERT_EQUAL(f_matrix.size(),6);
END_TEST

BEGIN_TEST(mul_1)
    ds::SymMatrix<int> f_matrix(4);
    ds::SymMatrix<int> s_matrix(4);
    double scalar = 5;
    f_matrix(0,0) = 5;
    f_matrix(1,2) = 3;
    f_matrix(2,3) = 7;
    f_matrix(0,1) = 1;
    f_matrix(2,2) = 9;
    f_matrix(0,2) = 2;
    s_matrix = f_matrix * scalar;
    ASSERT_EQUAL(s_matrix(0,0), 25);
    ASSERT_EQUAL(s_matrix(1,2),  15);
    ASSERT_EQUAL(s_matrix(2,3), 35);
    ASSERT_EQUAL(s_matrix(0,1), 5);
    ASSERT_EQUAL(s_matrix(2,2), 45);
    ASSERT_EQUAL(s_matrix(0,2), 10);
END_TEST

BEGIN_TEST(mul_2)
    ds::SymMatrix<int> f_matrix(4);
    ds::SymMatrix<int> s_matrix(4);
    double scalar = 5;
    f_matrix(0,0) = 5;
    f_matrix(1,2) = 3;
    f_matrix(2,3) = 7;
    f_matrix(0,1) = 1;
    f_matrix(2,2) = 9;
    f_matrix(0,2) = 2;
    s_matrix = scalar * f_matrix;
    ASSERT_EQUAL(s_matrix(0,0), 25);
    ASSERT_EQUAL(s_matrix(1,2),  15);
    ASSERT_EQUAL(s_matrix(2,3), 35);
    ASSERT_EQUAL(s_matrix(0,1), 5);
    ASSERT_EQUAL(s_matrix(2,2), 45);
    ASSERT_EQUAL(s_matrix(0,2), 10);
END_TEST




TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
        IGNORE_TEST(init)
        TEST(add_num)
        TEST(add_num_1)
        TEST(cctor)
        TEST(cctor_long)
        TEST(equal_op)
        TEST(add_equal_op)
        TEST(add_op)
        TEST(self_assignment)
        TEST(op_equal_long_int)
        TEST(op_add_long_int)
        TEST(op_add_equal_long_int)
        TEST(op_cout)
        TEST(mul_1)
        TEST(mul_2)
    
END_SUITE
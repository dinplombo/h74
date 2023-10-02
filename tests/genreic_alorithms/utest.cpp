#include "mu_test.h"
#include "genreic_alorithms.hpp"

#include <iostream>
#include <vector>
#include <list>

using namespace ga;

class Person{
public:
    explicit Person(char const* a_name);

    friend std::ostream& operator<<(std::ostream& a_out, Person const& a_Person);

private:
    char const* m_name;
};

Person::Person(char const* a_name)
:m_name(a_name)
{
}

std::ostream& operator<<(std::ostream& a_out, Person const& a_person)
{
    a_out << a_person.m_name;
    return a_out;
}

BEGIN_TEST(print_vector)
    std::vector<int> e;  
    std::vector<int> o(1,6);  
    std::vector<int> v(3,4);  
    std::cout << e;
    std::cout << o;
    std::cout << v;
    
    ASSERT_PASS();
END_TEST


BEGIN_TEST(print_list)
    std::list<int> e;  
    std::list<int> o(1,6);  
    std::list<int> v(3,4);  
    std::cout << e;
    std::cout << o;
    std::cout << v;
    
    ASSERT_PASS();
END_TEST

BEGIN_TEST(print_Person)
    std::vector<Person> p;
    p.push_back(Person("yosi"));
    p.push_back(Person("ori"));
    std::cout << p;
    
    ASSERT_PASS();
END_TEST


BEGIN_TEST(subrange_print)
    std::list<int> e;  
    for (size_t i = 0; i < 10; ++i){
        e.push_back(i);
    }
    std::list<int>::iterator next = e.begin();
    for (size_t i = 0; i < 2; ++i){
        ++next;
    }
    print(next, e.end());
    ASSERT_PASS();
END_TEST

BEGIN_TEST(subrange_print_person)
    std::vector<Person> p;
    p.push_back(Person("yosi"));
    p.push_back(Person("ori"));
    p.push_back(Person("niso"));
    std::vector<Person>::iterator next = p.begin();
    ++next;
    print(next, p.end());
    ASSERT_PASS();
END_TEST

BEGIN_TEST(multi)
    std::vector<int> v(3,10);
    int result = mul<int>(v.begin(), v.end());
    std::cout << result;
    ASSERT_EQUAL(result, 1000);
END_TEST

BEGIN_TEST(multi_vector_int)
    std::vector<int> v(3,10);
    int result = mul<int>(v.begin(), v.end());
    std::cout << result;
    ASSERT_EQUAL(result, 1000);
END_TEST

BEGIN_TEST(multi_lsit_double)
    std::list<double> v(3,2.2);
    double result = mul<double>(v.begin(), v.end());
    std::cout << result;
    ASSERT_THAT(abs(result - 10.648) < 0.00001);
END_TEST


BEGIN_TEST(foldit_func_vector)
    std::vector<int> v;
    v.push_back(3);
    v.push_back(7);
    v.push_back(10);
    v.push_back(20);
    std::cout << foldit<int>(v.begin(), v.end(), add);
    std::cout << "\n";
    std::cout << foldit<int>(v.begin(), v.end(), mul);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(foldit_func_list)
    std::list<int> l;
    l.push_back(3);
    l.push_back(7);
    l.push_back(10);
    l.push_back(20);
    std::cout << foldit<int>(l.begin(), l.end(), add);
    std::cout << "\n";
    std::cout << foldit<int>(l.begin(), l.end(), mul);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(splice_two_sort)
    std::vector<int> v;
    for (size_t i = 0; i < 6; ++i){
            v.push_back(i * 3);
    };
    std::vector<int> e;
    for (size_t i = 0; i < 6; ++i){
            e.push_back(i * 2);
    };
    std::vector<int> r(14);
    merge(v, e, r);
    std::cout << r;
    ASSERT_PASS();
END_TEST

BEGIN_TEST(replace_left_vector)
    std::vector<int> v;
    v.push_back(1);
    v.push_back(5);
    v.push_back(2);
    v.push_back(1);
    v.push_back(4);
    v.push_back(4);
    v.push_back(7);
    v.push_back(2);
    replace_with_left_bigger(v);
    print(v.begin(), v.end());
    ASSERT_PASS();
END_TEST

BEGIN_TEST(replace_left_list)
    std::list<double> l;
    l.push_back(1.1);
    l.push_back(5.5);
    l.push_back(2.2);
    l.push_back(1.1);
    l.push_back(4.1);
    l.push_back(4.1);
    l.push_back(7.1);
    l.push_back(2.1);
    replace_with_left_bigger(l);
    print(l.begin(), l.end());
    ASSERT_PASS();
END_TEST






TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
      TEST(print_vector)
      TEST(print_list) 
      TEST(print_Person)
      TEST(subrange_print)
      TEST(subrange_print_person)
      TEST(multi_vector_int)
      TEST(multi_lsit_double)
      TEST(foldit_func_list)
      TEST(foldit_func_vector)
      TEST(splice_two_sort)
      TEST(replace_left_vector)
      TEST(replace_left_list)
    
END_SUITE
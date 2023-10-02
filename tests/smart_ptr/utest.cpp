#include "mu_test.h"
#include "smart_ptr.hpp"
#include "stack.hpp"

#include <typeinfo> //tpyenino
#include <utility> //swap
#include <iostream> //cout

using namespace Ptr;
using namespace ds;

BEGIN_TEST(const_derefernce)
    Stack const* ptr = new Stack(17);
    ASSERT_THAT((*ptr).capacity() == 17);
    delete ptr;
    SmartPtr<Stack> const ptr_smart_ptr{new Stack(17)};
    try{
        ASSERT_THAT((*ptr_smart_ptr).capacity() == 17);
    }catch(...){
        std::cout << "nullptr\n";
    }
END_TEST

BEGIN_TEST(derefernce)
    Stack* ptr = new Stack(17);
    Stack stack(12);
    *ptr = stack;
    ASSERT_THAT((*ptr).capacity() == 12);
    delete ptr;
    SmartPtr<Stack> ptr_smart_ptr{new Stack(17)};
    try{
        *ptr_smart_ptr = stack;
        ASSERT_THAT((*ptr_smart_ptr).capacity() == 12);
    }catch(...){
        std::cout << "nullptr\n";
    }
END_TEST

BEGIN_TEST(arrow_operator)
    Stack* ptr = new Stack(17);
    ptr->push(3);
    ASSERT_THAT(ptr->size() == 1);
    delete ptr;
    SmartPtr<Stack> ptr_smart_ptr{new Stack(17)};
    ptr_smart_ptr->push(3);
    ASSERT_THAT(ptr_smart_ptr->size() == 1);
END_TEST

BEGIN_TEST(arrow_const_operator)
    Stack const* ptr = new Stack(17);
    ASSERT_THAT(ptr->size() == 0);
    delete ptr;
    SmartPtr<Stack> const ptr_smart_ptr{new Stack(17)};
    ASSERT_THAT(ptr_smart_ptr->size() == 0);
END_TEST

BEGIN_TEST(bool_operator) 
    Stack* ptr = new Stack(17);
    ASSERT_THAT(ptr != 0);
    delete ptr;
    SmartPtr<Stack> ptr_smart_ptr{new Stack(17)};
    ASSERT_THAT(!ptr_smart_ptr == 0);
END_TEST

BEGIN_TEST(move_ctor)
    SmartPtr<Stack> first_smart_ptr{new Stack(17)};
    SmartPtr<Stack> second_smart_ptr{std::move(first_smart_ptr)};

    ASSERT_PASS();
END_TEST

BEGIN_TEST(move_assign)
    SmartPtr<Stack> first_smart_ptr{new Stack(17)};
    SmartPtr<Stack> second_smart_ptr{new Stack(12)};
    first_smart_ptr->push(2);
    second_smart_ptr = std::move(first_smart_ptr);
    ASSERT_EQUAL(second_smart_ptr->size(),1);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(operator_equal) 
    Stack* ptr = new Stack(17);
    ASSERT_THAT(ptr == ptr);
    delete ptr;
    SmartPtr<Stack> ptr_smart_ptr{new Stack(17)};
    ASSERT_THAT(ptr_smart_ptr == ptr_smart_ptr);
END_TEST

BEGIN_TEST(not_operator_equal) 
    Stack* first_ptr = new Stack(17);
    Stack* second_ptr = new Stack(17);
    ASSERT_THAT(first_ptr != second_ptr);
    delete second_ptr;
    delete first_ptr;
    SmartPtr<Stack> first_smart_ptr{new Stack(17)};
    SmartPtr<Stack> seconf_smart_ptr{new Stack(17)};
    ASSERT_THAT(first_smart_ptr != seconf_smart_ptr);
END_TEST

BEGIN_TEST(cast_to_void) 
    Stack* first_ptr = new Stack(17);
    ASSERT_THAT(typeid((void*)first_ptr) == typeid(void*));
    delete first_ptr;
    SmartPtr<Stack> first_smart_ptr{new Stack(17)};
    ASSERT_THAT(typeid((void*)first_smart_ptr) == typeid(void*));
END_TEST

BEGIN_TEST(swap) 
    Stack* first_ptr = new Stack(17);
    Stack* second_ptr = new Stack(12);
    std::swap(first_ptr, second_ptr);
    ASSERT_THAT(first_ptr->capacity() == 12);
    ASSERT_THAT(second_ptr->capacity() == 17);
    delete first_ptr;
    delete second_ptr;
    SmartPtr<Stack> first_smart_ptr{new Stack(17)};
    SmartPtr<Stack> second_smart_ptr{new Stack(12)};
    first_smart_ptr.swap(second_smart_ptr);
    ASSERT_THAT(first_smart_ptr->capacity() == 12);
    ASSERT_THAT(second_smart_ptr->capacity() == 17);
END_TEST

BEGIN_TEST(print) 
    Stack* first_ptr = new Stack(17);
    std::cout << first_ptr << '\n';
    delete first_ptr;
    SmartPtr<Stack> first_smart_ptr{new Stack(17)};
    std::cout << first_smart_ptr << '\n';
    ASSERT_PASS();
END_TEST

// BEGIN_TEST(operator_equal_stack_int)
//     Stack* ptr = new Stack(17);
//     ASSERT_THAT(ptr == ptr);
//     delete ptr;
//     SmartPtr<Stack> ptr_smart_ptr{new Stack(17)};
//     SmartPtr<int> ptr_smart_ptr1{new int(17)};
//     ASSERT_THAT(ptr_smart_ptr != ptr_smart_ptr1);
// END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    // TEST(operator_equal_stack_int)
    TEST(derefernce)
    TEST(const_derefernce)
    TEST(arrow_operator)
    TEST(arrow_const_operator)
    TEST(bool_operator)
    TEST(operator_equal)
    TEST(move_ctor)
    TEST(move_assign)
    TEST(not_operator_equal)
    TEST(cast_to_void)
    TEST(swap) 
    TEST(print)
        
END_SUITE
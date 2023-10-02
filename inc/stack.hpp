#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

namespace ds
{

class Stack {
public:
    explicit Stack(size_t a_capacity); 

    ~Stack();
    Stack(Stack const& a_other);
    Stack(Stack&& a_other);
    Stack& operator=(Stack const& a_other);
    Stack& operator=(Stack&& a_other);

    size_t capacity() const;
    int* data_array() const; //function to get m_data for check the init test

    Stack& push(int a_item);
    Stack& pop(int& a_peek);
    const Stack& peek(int& a_peek) const;
    void print() const;

    void swap(Stack& a_other);
    size_t size() const;
    bool is_empty() const;
    bool is_full() const;

    Stack& operator+=(Stack& a_stack);

private:
    size_t m_capacity;
    size_t m_top;
    int* m_data;
    
};

void drain(Stack& a_destination, Stack& a_source);




}//namespace ds


#endif // STACK_HPP

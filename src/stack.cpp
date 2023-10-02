#include "stack.hpp"



#include <cstddef>  //size_t
#include <cstring>  //memcpy
#include <iostream>
#include <cassert>

namespace ds{

Stack::Stack(size_t a_capacity)
:m_capacity(a_capacity)
,m_top(0)
,m_data(new int[m_capacity])
{
}

Stack::~Stack()
{
    delete[] m_data;
}

Stack::Stack(Stack const& a_other)
: m_capacity(a_other.m_capacity)
, m_top(a_other.m_top)
{
    m_data = new int[sizeof(int) * a_other.m_capacity];
    int* d = &m_data[0];
    int* s = &a_other.m_data[0];
    memcpy(d, s, a_other.size() * sizeof(int));  
}

Stack::Stack(Stack&& a_other)
: m_capacity(a_other.m_capacity)
, m_top(a_other.m_top)
, m_data(a_other.m_data)
{
    a_other.m_data = nullptr;
    a_other.m_top = 0;
    a_other.m_capacity = 0;
    std::cout << "move cctor\n";
}

void Stack::swap(Stack& a_other)
{
    std::swap(m_capacity, a_other.m_capacity);
    std::swap(m_top, a_other.m_top);
    std::swap(m_data, a_other.m_data);
}

Stack& Stack::operator=(Stack const& a_other)
{
    if(this != &a_other){
        Stack c(a_other);
        swap(c);
    }
    return *this;
}

Stack& Stack::operator=(Stack&& a_other)
{

     if(this != &a_other){
        Stack c(std::move(a_other));
        swap(c);
        std::cout << "move op=\n";

    }
    return *this;
}

Stack& Stack::push(int a_item) 
{
    assert(not this->is_full());
    if(is_full()){
        return *this;
    }
    m_data[m_top++] = a_item;
    return *this;
}

const Stack& Stack::peek(int& a_peek) const 
{
    assert(not is_empty());
    if(is_empty()){
        return *this;
    }
    a_peek =  m_data[m_top-1];
    return *this;
}

Stack& Stack::pop(int& a_peek) 
{
    assert(not is_empty());
    if(is_empty()){
        return *this;
    }
    a_peek =  m_data[--m_top];
    return *this;;
}

size_t Stack::size() const
{
    return m_top;
}

void Stack::print() const
{
    size_t i;
    std::cout << "Stack: [";
    for(i = 0; i < m_top - 1; ++i){
        std::cout << m_data[i] << "; ";
    }
    std::cout << m_data[i] << "]\n";
}

bool Stack::is_empty() const
{
    return m_top == 0;
}

bool Stack::is_full() const
{
    return m_top == m_capacity;
}

size_t Stack::capacity() const
{
    return m_capacity;
}

int* Stack::data_array() const
{
    return m_data;
}

void drain(Stack& a_destination, Stack& a_source)
{
    assert (a_destination.capacity() >= a_destination.size() + a_source.size());
    if (a_destination.capacity() < a_destination.size() + a_source.size()){
        return;
    }
    size_t size = a_source.size();
    int pull_item;
    for (size_t i = 0; i < size; ++i){
        a_source.pop(pull_item);
        a_destination.push(pull_item);
    }
}

Stack& Stack::operator+=(Stack& a_stack)
{
    assert (capacity() >= size() + a_stack.size());
    if (capacity() < size() + a_stack.size()){
        return *this;
    }
    int* d = m_data + size();
    int* s = a_stack.m_data;
    memcpy(d, s, a_stack.size() * sizeof(int));
    m_top += a_stack.size();
    a_stack.m_top = 0;
    return *this;
}





} //namespace ds
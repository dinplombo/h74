#include "ministack.hpp"
#include "stack.hpp"

#include <cstdio>
#include <cstddef>
#include <iostream>
#include <cassert>

namespace ds{

Ministack::Ministack(size_t a_capacity)
:m_original(a_capacity)
,m_ministack(2*a_capacity)
,m_capacity(a_capacity)
{
}


Ministack&  Ministack::push(int a_item)
{
    assert(not m_original.is_full());
    assert(not m_ministack.is_full());
    if (m_original.is_empty())
    {
        m_min_value = a_item;
    }
    if (m_min_value > a_item){
        m_min_value = a_item;
    }
    m_original.push(a_item);
    m_ministack.push(a_item);
    m_ministack.push(m_min_value);
    return *this;
}


int Ministack::pop()
{
    assert(not m_original.is_empty());
    int pop_value;
    int peek_value;
    m_ministack.pop(pop_value);
    m_ministack.pop(pop_value);
    m_ministack.peek(peek_value);
    m_min_value = peek_value;
    m_original.pop(pop_value);
    return pop_value;
}

size_t Ministack::capacity() const
{
    return m_capacity;
}

size_t Ministack::size() const
{
    return m_original.size();
}

bool Ministack::is_empty() const
{
    return m_original.is_empty();
}

bool Ministack::is_full() const
{
    return m_original.is_full();

}

int Ministack::min()
{
    assert(not m_original.is_empty());
    return m_min_value;
}


} //ds namespace
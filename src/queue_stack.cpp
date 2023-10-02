#include "queue_stack.hpp"
#include "stack.hpp"

#include <cstdio>
#include <cstddef>
#include <iostream>
#include <cassert>

namespace ds{

QueueStack::QueueStack(size_t a_capacity)
:m_push_stack(a_capacity)
,m_pop_stack(a_capacity)
,m_capacity(a_capacity)
{
}



QueueStack&  QueueStack::push(int a_item)
{
    assert(not is_full());
    if(not is_full()){
        if (m_capacity == m_push_stack.size()){
            ds::drain(m_pop_stack, m_push_stack);
        }
        m_push_stack.push(a_item);
    }
    return *this;
}


QueueStack& QueueStack::pop(int& a_value)
{
    assert(not is_empty());
    if(is_empty()){
        return *this;
    }
    if (m_pop_stack.is_empty() && !(m_push_stack.is_empty())){
        ds::drain(m_pop_stack, m_push_stack);
    }
    m_pop_stack.pop(a_value);
    return *this;
}

size_t QueueStack::capacity() const
{
    return m_capacity;
}

size_t QueueStack::size() const
{
    return (m_pop_stack.size() + m_push_stack.size());
}

bool QueueStack::is_empty() const
{
    return (m_pop_stack.is_empty() && m_push_stack.is_empty());
}

bool QueueStack::is_full() const
{
    return (m_capacity == m_push_stack.size() && !(m_pop_stack.is_empty()));
}

} //ds namespace
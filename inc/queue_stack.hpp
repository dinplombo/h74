#ifndef QUEUE_STACK_HPP
#define QUEUE_STACK_HPP

#include <cstddef>

#include "stack.hpp"

namespace ds
{

class QueueStack {
public:
    explicit QueueStack(size_t a_capacity); 

    QueueStack& push(int a_item);
    QueueStack& pop(int& a_value);
    size_t capacity() const;
    
    size_t size() const;
    bool is_empty() const;
    bool is_full() const; 

private:
    Stack m_push_stack;
    Stack m_pop_stack;
    size_t m_capacity;
};



}//namespace ds


#endif // QUEUE_STACK_HPP

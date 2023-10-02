#ifndef MINISTACK_HPP
#define MINISTACK_HPP

#include <cstddef>

#include "stack.hpp"

namespace ds
{

class Ministack {
public:
    explicit Ministack(size_t a_capacity);


    ~Ministack() = default;
    Ministack(Ministack const& a_other) =  default;
    Ministack& operator=(Ministack const& a_other) = default; 

    Ministack& push(int a_item);
    int min();
    int pop();
    size_t capacity() const;

    size_t size() const;
    bool is_empty() const;
    bool is_full() const;    
    

private:
    Stack m_original;
    Stack m_ministack;
    int m_min_value;
    size_t m_capacity;
    
};



}//namespace ds


#endif // MINISTACK_HPP

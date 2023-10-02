#include "helpers.hpp"
#include <cstddef> //size_t

namespace helpers
{

void swap(int& a_first, int& a_second)
{
    int old_first = a_first;
    a_first = a_second;
    a_second = old_first;
}

size_t artimetic_sequence(size_t a_dim)
{
    return ((a_dim * (1 + a_dim))/2);
}

}//namespace helpers

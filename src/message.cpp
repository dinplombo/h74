#include "message.hpp"

#include <iostream>

namespace AbsMessage
{

bool operator==(Message const& a_lhs, Message const& a_rhs)
{
    std::string::const_iterator left_current = a_lhs.begin();
    std::string::const_iterator right_current = a_rhs.begin();
    while (left_current != a_lhs.end()){
        if(*left_current != *right_current){
            return false;
        }
        ++left_current;
        ++right_current;
    }
    if(right_current != a_rhs.end()){
        return false;
    }
    return true;
}

} //namespace AbsMessage
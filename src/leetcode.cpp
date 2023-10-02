#include "leetcode.hpp"

#include <string> //string
#include <iostream> //stringstream
#include <unordered_map>


namespace AbsMessage
{

LeetCode::LeetCode()
: m_leet{
            {'a', "4"}, {'b', "8"}, {'c', "("}, {'d', ")"}, {'e', "3"}, {'f', "|="}, {'g', "6"}, {'h', "|-|"}, 
            {'i', "1"}, {'j', "_|"}, {'k', "|<"}, {'l', "|_"}, {'m', "/v\\"}, {'n', "^/"}, {'o', "()"}, 
            {'p', "|>"}, {'q', "9"}, {'r', "|`"}, {'s', "5"}, {'t', "7"}, {'u', "(_)"}, {'v', "\\/"}, 
            {'w', "\\/\\/"}, {'x', "><"}, {'y', "\\//"}, {'z', "2"}
        }
{
}

std::string LeetCode::translate(char a_char)
{
    return m_leet[a_char];
}


} //namespace AbsMessage
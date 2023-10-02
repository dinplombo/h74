#include "scytale.hpp"

#include <string> //string
#include <iostream> //stringstream
#include <algorithm> //remove

namespace AbsMessage
{

Scytale::Scytale(size_t a_letters_round)
: m_letters_round(a_letters_round)
{
}

namespace {
std::string remove_blanks(std::string::const_iterator a_current, std::string::const_iterator a_end){
    std::string result_str;
    while (a_current != a_end){
        if (*a_current == ' ' ){
            ++a_current;
            continue;
        }
        result_str += *a_current;
        ++a_current;
    }
    return result_str;
}
} //namespace 

void Scytale::encode(Message const& a_source, Message& a_encoded)
{
    std::string origin_str;
    std::string result_str;
    origin_str = remove_blanks(a_source.begin(), a_source.end());
    size_t str_len = origin_str.length();
    
    for (size_t i = 0; i <= str_len / m_letters_round; ++i) {
        for (size_t j = i; j < str_len; j += m_letters_round) {
            result_str.push_back(origin_str[j]);
        }
    }
    a_encoded.append(result_str);
}


} //namespace AbsMessage
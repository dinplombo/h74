#include "transposition_ciper.hpp"
#include "message.hpp"

#include <unordered_map>
#include <cstddef> //size_t
#include <algorithm>
#include <iostream>

namespace AbsMessage
{

namespace{
std::string remove_blanks(std::string::const_iterator a_current, std::string::const_iterator a_end){
    std::string result_str;
    while (a_current != a_end){
        if (*a_current == ' ' || *a_current == '\0'){
            ++a_current;
            continue;
        }
        result_str += *a_current;
        ++a_current;
    }
    return result_str;
}

void pack_in_map(Message const &a_source, std::unordered_map<char, std::string>& a_word_map, std::string a_key_word){
    std::string noblanks_str;
    noblanks_str = remove_blanks(a_source.begin(), a_source.end());
    size_t counter = 0;
    char key_char;

    for (size_t i = 0; i < a_key_word.size();  i = (i + 1) % a_key_word.size()){
        if (counter >= noblanks_str.size() ){ 
            key_char = a_key_word[i];
            a_word_map[key_char].push_back('x');
            if(counter % a_key_word.size() == 0){//to example str = 16 but key_word == 6 so the loop need to stop in 18
                break;
            }
            ++counter;
        }

        key_char = a_key_word[i];
        a_word_map[key_char].push_back(noblanks_str[counter]);
        ++counter; 
    }
}

void unpack_from_map(std::unordered_map<char, std::string>& a_word_map, std::string a_key_word, std::string& a_noblanks_str){
    size_t counter = 0;
    char key_char;
    std::string noblanks_str;
    std::string current_str;
    std::string sort_key = a_key_word;
    std::sort(sort_key.begin(), sort_key.end());
    for (size_t i = 0; i < a_key_word.size();  ++i){
        key_char = sort_key[i];
        current_str.append(a_word_map[key_char]);
    }

    std::string fix_str;

    for (size_t i = 0; i < a_key_word.size();  i = (i + 1)%a_key_word.size()){
        if (counter >= current_str.size() && counter % a_key_word.size() == 0){
            break;
        }
        fix_str.push_back(current_str[i*3 + counter / a_key_word.size()]);
        ++counter;
    }

    a_noblanks_str = remove_blanks(fix_str.begin(), fix_str.end());
}


} //namespace

    void TranspositionEncryption::encode(Message const &a_source, Message &a_encoded)
    {
        std::unordered_map<char, std::string> word_map;
        std::string noblanks_str;
        pack_in_map(a_source, word_map, m_key_word);
        unpack_from_map(word_map, m_key_word, noblanks_str);
        a_encoded.append(noblanks_str);

    }

    TranspositionEncryption::TranspositionEncryption(std::string a_key)
    :m_key_word(a_key)
    {
    }

} // namespace AbsMessage


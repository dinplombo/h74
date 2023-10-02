#include "frequency_table.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <algorithm>

namespace {
bool sort_func (std::pair<std::string, size_t> a_first, std::pair<std::string, size_t> a_second){
    return a_first.second > a_second.second;
}

void letter_count(std::vector<size_t>& a_vector, std::string& a_word){
    size_t i = 0;
    while (a_word[i] != '\0'){
        // std::cout << a_word[i] << "\n";
        if (a_word[i] == '\n'){
            return;
        }
        if (a_word[i] >= 'A' && a_word[i] <= 'Z'){
            a_word[i] = a_word[i] + 32;
        }
        a_vector[a_word[i] - 'a']++;
        if (a_word[i] < 'A' || (a_word[i] > 'Z' && a_word[i] < 'a') || a_word[i] > 'z'){
            a_word.erase(i,1);
            --i;
        }
        ++i;
    }
}

void word_count(std::unordered_map<std::string, size_t>& a_word_map, std::string& a_word){
    size_t current_count = a_word_map[a_word];
    std::unordered_map<std::string, size_t>::iterator itr;
    itr = a_word_map.find(a_word);
    itr->second = ++current_count;
}

void print_map(std::vector<std::pair<std::string, size_t>>& a_word_vector, size_t a_num_print){
    std::cout << "word frequences:" << '\n';
    size_t counter = 1 ;
    for (size_t i = 0; i < a_word_vector.size(); ++i){
        std::cout << a_word_vector[i].first << ":" << a_word_vector[i].second << '\n';
        if (a_num_print == counter){
            break;
        }
        ++counter;
    }
}
} //namespace

std::vector<size_t> ds::frequency_table(std::istream &a_in, size_t a_num_print)
{
    std::vector<size_t> letters_vector(26);
    std::unordered_map<std::string, size_t> word_map;
    std::string word;
    while (a_in >> word){
        letter_count(letters_vector, word);
        word_count(word_map, word);
    }
    std::vector<std::pair<std::string, size_t>> word_vector(word_map.begin(), word_map.end());
    std::sort(word_vector.begin(), word_vector.end(), sort_func);
    std::cout << "letters frequences:" << '\n';
    ds::print(letters_vector);
    print_map(word_vector, a_num_print);
    return letters_vector;
}



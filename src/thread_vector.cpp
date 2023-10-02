#include "thread_vector.hpp"

#include <iostream>
#include <thread>
#include <iterator>

#include <time.h> //time
#include <stdlib.h> //srand rand

namespace thread {
int counter = 0;
unsigned long int capacity = 10'000'000;

void init_random_vector(std::vector<int>& a_vector)
{
    std::srand (time(NULL));

    for(size_t i = 0; i < capacity; ++i){
        a_vector.push_back(rand() % capacity + 1);
    }

}

int count_div_3_5(std::vector<int> * a_vector, size_t a_begin_index, size_t a_end_index)
{
    auto begin_itr(a_vector->cbegin());
    auto end_itr(a_vector->cbegin());
    std::advance(begin_itr, a_begin_index);
    std::advance(end_itr, a_end_index);

    while (begin_itr != end_itr){
        if (*begin_itr % 5 == 0 || *begin_itr % 3 == 0){
            ++counter;
        }
        ++begin_itr;
    }

    return counter;
}

void thread_counter(std::vector<int>& a_vector, size_t num_thread)
{
    size_t begin_index = 0;
    size_t split_inedx = a_vector.size() / num_thread;
    std::vector<std::thread> thread_vector;

    for(size_t i = 0; i < num_thread; ++i){
		std::thread t{count_div_3_5, &a_vector, begin_index, begin_index + split_inedx};
        thread_vector.push_back(std::move(t));
        begin_index += split_inedx;
    }

    for (auto& thread : thread_vector){
        thread.join();
    }
}

//////////////////////////


int count_div_15(std::vector<int> const& a_vector, size_t a_begin_index, size_t a_end_index)
{
    auto begin_itr(a_vector.cbegin());
    auto end_itr(a_vector.cbegin());
    std::advance(begin_itr, a_begin_index);
    std::advance(end_itr, a_end_index);

    while (begin_itr != end_itr){
        if (*begin_itr % 15 == 0 ){
            ++counter;
        }
        ++begin_itr;
    }

    return counter;
}


void thread_counter_2(std::vector<int>& a_vector, size_t num_thread)
{
    size_t begin_index = 0;
    size_t split_inedx = a_vector.size() / num_thread;
    std::vector<std::thread> thread_vector;

    for(size_t i = 0; i < num_thread; ++i){
		std::thread t{count_div_15, std::cref(a_vector), begin_index, begin_index + split_inedx};
        thread_vector.push_back(std::move(t));
        begin_index += split_inedx;
    }

    for (auto& thread : thread_vector){
        thread.join();
    }
}


} //namespace thread

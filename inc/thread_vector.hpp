#ifndef THREAD_VECTOR_HPP
#define THREAD_VECTOR_HPP

#include <vector>
#include <cstddef> //size_t

namespace thread {

void init_random_vector(std::vector<int>& a_vector);
int count_div_3_5(std::vector<int>* a_vector, size_t a_begin_index, size_t a_end_index);
void thread_counter(std::vector<int>& a_vector, size_t num_thread = 1);

} //namespace thread

#endif // THREAD_VECTOR_HPP
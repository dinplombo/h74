#ifndef FREQUENCE_TABLE_HPP
#define FREQUENCE_TABLE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include "genreic_alorithms.hpp" 


namespace ds
{

std::string read_from_stdin(std::istream &a_in);

std::vector<size_t> frequency_table(std::istream &a_in, size_t a_num_print);

template<typename Container>
void print(Container const& a_container, std::ostream& a_out = std::cout)
{
    ga::print(a_container.begin(), a_container.end(), a_out);
}

} // namespace ds

#endif // FREQUENCE_TABLE

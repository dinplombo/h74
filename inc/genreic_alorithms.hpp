#ifndef GENRIC_ALGORITHMS_HPP
#define GENRIC_ALGORITHMS_HPP


#include <iostream> //cout

namespace ga{

template<typename Container, typename T = typename Container::value_type>
std::ostream& operator<<(std::ostream& a_out, Container const& a_container)
{
   typename Container::const_iterator begin = a_container.cbegin();
   typename Container::const_iterator end = a_container.cend();
   a_out << "[" ;
   while (begin != end){
    a_out << *begin ;
    ++begin;
    if (begin != end){
        a_out <<  ",";
    }
   }
   a_out << "]" << "\n";
   return a_out;
}

template<typename Iterator>
void print(Iterator const& a_start, Iterator const& a_end, std::ostream& a_out = std::cout)
{
    a_out << "[";
    Iterator itr = a_start;
    while (itr!= a_end){
        a_out << *itr;
        itr++;
        if (itr!= a_end){
            a_out << ",";
        }
    }
    a_out << "]" << "\n";
}

template<typename T ,typename Iterator>
T mul(Iterator const& a_start, Iterator const& a_end)
{
    T result = 1;
    Iterator itr = a_start;
    while (itr != a_end){
        result *= *itr;
        ++itr;
    }
    return result;
}

template<typename T ,typename Iterator>
T add(Iterator const& a_start, Iterator const&  a_end)
{
    T result = 0;
    Iterator itr = a_start;
    while (itr != a_end){
        result += *itr;
        ++itr;
    }
    return result;
}


template<typename T ,typename Iterator>
T foldit(Iterator const& a_start, Iterator const& a_end, T(*func)(Iterator const& a, Iterator const& b))
{
    return func(a_start, a_end);
}

template<typename Container, typename T = typename Container::value_type>
void merge(Container const& a_lhs_container, Container const& a_rhs_container, Container& a_result_container)
{
    typename Container::const_iterator lhs_begin = a_lhs_container.begin();
    typename Container::const_iterator rhs_begin = a_rhs_container.begin();
    typename Container::const_iterator lhs_end = a_lhs_container.end();
    typename Container::const_iterator rhs_end = a_rhs_container.end();
    a_result_container.clear();
    while(rhs_begin != rhs_end and lhs_begin != lhs_end){ 
        if (*lhs_begin <= *rhs_begin){
            a_result_container.push_back(*lhs_begin);
            ++lhs_begin;

        }
        else{
            a_result_container.push_back(*rhs_begin);
            ++rhs_begin;
        }
    }
    
    while(rhs_begin != rhs_end){
            a_result_container.push_back(*rhs_begin);
            ++rhs_begin;
    }
    while(lhs_begin != lhs_end){
            a_result_container.push_back(*lhs_begin);
            ++lhs_begin;
        }
     
}

template<typename Container, typename T = typename Container::value_type>
void replace_with_left_bigger(Container& a_container)
{
    typename Container::iterator current = a_container.begin();
    typename Container::iterator next = a_container.begin();
    ++next;
    while (current != a_container.end()) {
        // typename Container::iterator temp = next;
        // ++next;
        while (next != a_container.end()){
            if (*current < *next){
                *current = *next;
                break;
            }
            ++next;
        }
        ++current;
        next = current;
        ++next;
    }
}


}// namespace ga

 

#endif // GENRIC_ALGORITHMS_HPP
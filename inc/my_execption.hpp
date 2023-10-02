#ifndef MY_EXECPTION_HPP
#define MY_EXECPTION_HPP

#include <stdexcept>

namespace my_execption {

class PoolException : public std::runtime_error {
public:
    using runtime_error::runtime_error;

};

} // namespace my_execption

#endif // MY_EXECPTION_HPP
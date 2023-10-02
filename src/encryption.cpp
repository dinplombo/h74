#include "encryption.hpp"


#include <string>
#include <cstddef> //size_t
#include <sstream>
#include <iostream>


en::Uppercase::~Uppercase()
{
}

std::string en::Uppercase::encode(std::istream& a_message)
{
    std::string message;
    a_message >>  message;
    for (size_t i = 0; i < message.length(); ++i){
        message[i] = toupper(message[i]);
    }
    return message;
}
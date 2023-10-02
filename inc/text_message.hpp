#ifndef TEXT_MESSAGE_HPP
#define TEXT_MESSAGE_HPP

#include "message.hpp"

#include <iostream>

#include <string>

namespace AbsMessage
{

class TextMessage : public Message{
public:
    TextMessage() = default; //ctor
    TextMessage(const char* a_other); //ctor
    TextMessage(std::string& a_other); //ctor
    TextMessage& operator=(TextMessage const& a_other) = default;

    std::string::iterator begin() override;
    std::string::const_iterator begin() const override ;
    std::string::iterator end() override;
    std::string::const_iterator end() const override ;
    TextMessage& append(std::string const& a_message) override;

    ~TextMessage() override = default;

private:
    std::string m_message;
};

 }// namespace AbsMessage

#endif // TEXT_MESSAGE_HPP
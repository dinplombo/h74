#include "text_message.hpp"

#include "string"

namespace AbsMessage {

std::string::iterator TextMessage::begin()
{
    return m_message.begin();
}

std::string::const_iterator TextMessage::begin() const
{
    return m_message.begin();
}

std::string::iterator TextMessage::end()
{
    return m_message.end();
}

std::string::const_iterator TextMessage::end() const
{
    return m_message.end();
}

TextMessage &TextMessage::append(std::string const& a_message)
{
   m_message.append(a_message);
   return *this;
}

TextMessage::TextMessage(const char*  a_other)
:m_message{a_other}
{
}

TextMessage::TextMessage(std::string& a_other)
:m_message{a_other}
{
}

} //namespace AbsMessage
#include "stream_base.hpp"

#include "text_message.hpp"
#include "message.hpp"

#include <iostream>
#include <utility>

namespace AbsMessage{

Message* StreamBase::recive_message()
{ 
    std::string line;
    Message* str_message = new TextMessage;
    std::getline(m_input, line);
    if (line == "" || m_input.eof()){
        return  NULL;
    }
    str_message->append(line);
    return str_message;
}

StreamBase::StreamBase(std::istream& a_input)
: m_input(a_input)
{
}

// StreamBase::~StreamBase()
// {
//     m_input.close();
// }


} //namespace AbsMessage
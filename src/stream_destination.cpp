#include "stream_destination.hpp"

#include "message.hpp"

#include <iostream>

namespace AbsMessage{

void StreamDestination::send_message(Message const& a_message)
{
    std::string::const_iterator current = a_message.begin();
    while (current != a_message.end()){
        m_out << *current;
        ++current;
    }
    m_out << '\n';
}

StreamDestination::StreamDestination(std::ostream& a_out)
: m_out(a_out)
{
}


} //namespace AbsMessage
#include "uppercase.hpp"
#include "message.hpp"

#include <string>

namespace AbsMessage {

void UpperCase::encode(Message const& a_source, Message& a_encoded)
{
    std::string::const_iterator current = a_source.begin(); 
    std::string upper_current; 
    while (current != a_source.end()){
        upper_current = toupper(*current);
        a_encoded.append(upper_current);
        ++current;
    }
}

} //namespace AbsMessage
#include "substitution_encoder.hpp"

namespace AbsMessage
{

void SubstitutionEncoder::encode(Message const &a_source, Message &a_encoded)
{
    std::string::const_iterator current = a_source.begin(); 
    
    while (current != a_source.end()){
        // char translated = translate(*current);
        // std::string str_current{translated};
        a_encoded.append(translate(*current));
        ++current;
    }
}

} //namespace AbsMessage
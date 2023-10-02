#include "caesar_encryption.hpp"
#include "message.hpp"



namespace AbsMessage
{

void CaesarEncryption::encode(Message const &a_source, Message &a_encoded)
{
    std::string::const_iterator current = a_source.begin();
    std::string upper_current;
    while (current != a_source.end())
    {
        upper_current = tocaesar(*current);
        a_encoded.append(upper_current);
        ++current;
    }
}

CaesarEncryption::CaesarEncryption(int a_shift_num)
:m_shift_num(a_shift_num)
{
}

std::string CaesarEncryption::tocaesar(char const a_char)
{
    std::string result;
    char increment_char = a_char;
    if (increment_char >= 'a' && increment_char <= 'z'){
        increment_char = (increment_char - 'a' + m_shift_num) % 26 + 'a';
    } else if (increment_char >= 'A' && increment_char <= 'Z') { 
    increment_char = (increment_char - 'A' + m_shift_num) % 26 + 'A';
    }
    result = increment_char;
    return result;
}

} // namespace AbsMessage


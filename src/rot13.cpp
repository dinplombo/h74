#include "rot13.hpp"
#include "caesar_encryption.hpp"

namespace AbsMessage
{

RotThirteen::RotThirteen()
:m_caesar(13)
{
}

void RotThirteen::encode(Message const& a_source, Message& a_encoded)
{
    return m_caesar.encode(a_source, a_encoded);
}


} // namespace AbsMessage
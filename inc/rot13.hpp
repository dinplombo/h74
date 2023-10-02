#ifndef ROT_13_HPP
#define ROT_13_HPP

#include "message.hpp"
#include "caesar_encryption.hpp"
#include "encoder.hpp"

#include <string>

namespace AbsMessage
{

class RotThirteen : public Encoder{
public:
    ~RotThirteen() override = default;
    void encode(Message const& a_source, Message& a_encoded) override;

    RotThirteen();
    RotThirteen(RotThirteen const& a_other) = default;
    RotThirteen& operator=(RotThirteen const& a_other) = default;

private:
CaesarEncryption m_caesar;

};

} // namespace AbsMessage

#endif // ROT_13_HPP
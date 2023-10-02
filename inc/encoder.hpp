#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "message.hpp"
#include <string>

namespace AbsMessage
{

class Encoder {
public:
    virtual ~Encoder() = default;
    virtual void encode(Message const& a_source, Message& a_encoded) = 0;

protected:
    Encoder() = default;
    Encoder(Encoder const& a_other) = default;
    Encoder& operator=(Encoder const& a_other) = default;

};

} // namespace AbsMessage

#endif // ENCODER_HPP
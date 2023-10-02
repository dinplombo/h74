#ifndef PRECIOUS_STONE_HPP
#define PRECIOUS_STONE_HPP

#include "message_source.hpp"
#include "message_destination.hpp"
#include "encoder.hpp"

namespace AbsMessage {

class PreciousStone {
public:
    PreciousStone(MessageSource& a_input, MessageDestination& a_out, Encoder& a_encoder);
    ~PreciousStone() = default;

    void execute() const; 

private:
    MessageSource&  m_input;
    MessageDestination&  m_out;
    Encoder&  m_encoder;

};

}// namespace AbsMessage

#endif // PRECIOUS_STONE_HPP
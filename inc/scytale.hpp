#ifndef SCYTALE_HPP
#define SCYTALE_HPP

#include "encoder.hpp"
#include "message.hpp"

#include <cstddef> //size_t


namespace AbsMessage
{
class Scytale : public Encoder {
public:
    ~Scytale() override = default;
    void encode(Message const& a_input, Message& a_output) override;

    explicit Scytale(size_t a_letters_round);

private:
    size_t m_letters_round;
};

} //namespace AbsMessage

#endif // SCYTALE_HPP

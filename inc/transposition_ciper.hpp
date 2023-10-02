#ifndef TRANSPOSITION_CIPER_HPP
#define TRANSPOSITION_CIPER_HPP

#include "message.hpp"
#include "encoder.hpp"

#include <string>

namespace AbsMessage
{
class TranspositionEncryption : public Encoder {
public:
    ~TranspositionEncryption() override = default;
    void encode(Message const& a_source, Message& a_encoded) override;


    TranspositionEncryption(std::string a_key);
    TranspositionEncryption(TranspositionEncryption const& a_other) = default;
    TranspositionEncryption& operator=(TranspositionEncryption const& a_other) = default;

private:
std::string m_key_word;

};

} // namespace AbsMessage

#endif // TRANSPOSITION_CIPER_HPP
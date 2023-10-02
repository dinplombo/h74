#ifndef CAESAR_ENCRYPTION_HPP
#define CAESAR_ENCRYPTION_HPP

#include "message.hpp"
#include "encoder.hpp"

#include <string>

namespace AbsMessage
{

class CaesarEncryption : public Encoder {
public:
    ~CaesarEncryption() override = default;
    void encode(Message const& a_source, Message& a_encoded) override;

    CaesarEncryption(int a_shift_num);
    CaesarEncryption(CaesarEncryption const& a_other) = default;
    CaesarEncryption& operator=(CaesarEncryption const& a_other) = default;

private:
std::string tocaesar(const char a_char);

private:
int m_shift_num;
};

} // namespace AbsMessage

#endif // CAESAR_ENCRYPTION_HPP
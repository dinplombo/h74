#ifndef SUBSTITUTION_ENCODER_HPP
#define SUBSTITUTION_ENCODER_HPP

#include "message.hpp"
#include "encoder.hpp"

#include <string>


namespace AbsMessage
{
class SubstitutionEncoder : public Encoder {
public:
    ~SubstitutionEncoder() override = default;
    void encode(Message const& a_source, Message& a_encoded) override;

protected:
    virtual std::string translate(char a_char) = 0;

protected:
    SubstitutionEncoder() = default;
    SubstitutionEncoder(SubstitutionEncoder const& a_other) = default;
    SubstitutionEncoder& operator=(SubstitutionEncoder const& a_other) = default;

};

} // namespace AbsMessage

#endif // SUBSTITUTION_ENCODER_HPP
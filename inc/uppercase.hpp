#ifndef UPPER_CASE_HPP
#define UPPER_CASE_HPP

#include "message.hpp"
#include "encoder.hpp"

#include <string>

namespace AbsMessage
{

class UpperCase : public Encoder {
public:
    ~UpperCase() override = default;
    void encode(Message const& a_source, Message& a_encoded) override;

    UpperCase() = default;
    UpperCase(UpperCase const& a_other) = default;
    UpperCase& operator=(UpperCase const& a_other) = default;

};

} // namespace AbsMessage

#endif // UPPER_CASE_HPP
#ifndef STREAM_BASE_HPP
#define STREAM_BASE_HPP

#include "message_source.hpp"
#include "message.hpp"

#include <iostream>
#include <fstream>

namespace AbsMessage
{

class StreamBase : public MessageSource{
public:
    ~StreamBase() override = default;
    Message* recive_message() override;

protected:
    StreamBase(std::istream& a_input);

private:
    std::istream& m_input;

};

}// namespace AbsMessage

#endif // STREAM_BASE_HPP
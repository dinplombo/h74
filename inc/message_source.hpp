#ifndef MESSAGE_SOURCE_HPP
#define MESSAGE_SOURCE_HPP

#include "text_message.hpp"

namespace AbsMessage
{

class MessageSource {
public:
    virtual ~MessageSource() = default;
    virtual Message* recive_message() = 0;

protected:
    MessageSource() = default;
    MessageSource(MessageSource const& a_other) = default;
    MessageSource& operator=(MessageSource const& a_other) = default;

};

}// namespace AbsMessage

#endif // MESSAGE_SOURCE_HPP
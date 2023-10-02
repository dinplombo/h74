#ifndef MESSAGE_DESTINATION_HPP
#define MESSAGE_DESTINATION_HPP

#include "message.hpp"

namespace AbsMessage
{

class MessageDestination {
public:
    virtual ~MessageDestination() = default;
    virtual void send_message(Message const& a_message) = 0;

protected:
    MessageDestination() = default;
    MessageDestination(MessageDestination const& a_other) = default;
    MessageDestination& operator=(MessageDestination const& a_other) = default;

};

}// namespace AbsMessage

#endif // MESSAGE_DESTINATION_HPP
#ifndef STREAM_DESTINATION_HPP
#define STREAM_DESTINATION_HPP

#include "message_destination.hpp"
#include "message.hpp"

#include <ostream>

namespace AbsMessage
{

class StreamDestination : public MessageDestination{
public:
    ~StreamDestination() override = default;
    void send_message(Message const& a_message) override;

protected:
    StreamDestination(std::ostream& a_out);

private:
    std::ostream& m_out;

};

}// namespace AbsMessage

#endif // STREAM_DESTINATION_HPP
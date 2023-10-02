#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace AbsMessage
{

class Message {
public:
    virtual ~Message() = default;
    virtual std::string::iterator begin() = 0;
    virtual std::string::const_iterator begin() const = 0;
    virtual std::string::iterator end() = 0;
    virtual std::string::const_iterator end() const = 0;
    virtual Message& append(std::string const& a_message) = 0;

protected:
    Message() = default;
    Message(Message const& a_other) = default;
    Message& operator=(Message const& a_other) = default;

};

bool operator==(Message const& a_lhs, Message const& a_rhs);

 }// namespace AbsMessage

#endif // MESSAGE_HPP
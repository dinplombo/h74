#include "precious_stone.hpp"
#include "text_message.hpp"

namespace AbsMessage
{
PreciousStone::PreciousStone(MessageSource& a_input, MessageDestination& a_out, Encoder& a_encoder)
:m_input{a_input}
,m_out{a_out}
,m_encoder{a_encoder}
{
}

void PreciousStone::execute() const
{
    TextMessage encoded_message;
    Message* str_message = m_input.recive_message();
    while (str_message != NULL){
        m_encoder.encode(*str_message, encoded_message);
        m_out.send_message(encoded_message);
        delete(str_message);
        str_message = m_input.recive_message();
    }
    delete(str_message);
}


} //namespace AbsMessage
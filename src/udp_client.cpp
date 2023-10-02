#include "udp_client.hpp"

#include <cstring>

namespace AbsMessage
{

UdpServer::UdpServer()
{
    if ( (m_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creae failed");
    }
   
    memset(&m_sin, 0, sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_port = htons(1050);
    m_sin.sin_addr.s_addr = inet_addr("127.0.0.1");

}

void UdpServer::send_message(Message const& a_message)
{
    std::string buffer;
    std::string::const_iterator current = a_message.begin();
    while (current != a_message.end()){
        buffer.push_back(*current);
        ++current;
    }
    // char char_buffer[1024]; 
    // strcpy(char_buffer, buffer.c_str()); //send buffer.c
    sendto(m_socket, buffer.c_str(), buffer.size(), 0, (const struct sockaddr *) &m_sin,  sizeof(m_sin));
}


} //namespace AbsMessage



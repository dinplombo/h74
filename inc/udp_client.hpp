#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

#include "message_destination.hpp"
#include "message.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace AbsMessage
{

class UdpServer : public MessageDestination{
public:
    UdpServer();
    ~UdpServer() override = default;
    void send_message(Message const& a_message) override;

private:
    struct sockaddr_in m_sin;
    int m_socket;

};

}// namespace AbsMessage

#endif // UDP_CLIENT_HPP
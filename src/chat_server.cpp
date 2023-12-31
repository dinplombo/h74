//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;

//----------------------------------------------------------------------

class chat_participant
{
public:
  virtual ~chat_participant() {}
  virtual void deliver(const chat_message& msg) = 0;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

class chat_room
{
public:
  void join(chat_participant_ptr participant)
  {
    participants_.insert(participant);
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }

  void deliver(const chat_message& msg)
  {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    for (auto participant: participants_)
      participant->deliver(msg);
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session : public chat_participant,
    public std::enable_shared_from_this<chat_session>
{
public:
  chat_session(tcp::socket socket, chat_room& room, bool a_type)
    : socket_(std::move(socket))
    , room_(room)
    , m_type(a_type)
  {
  }

  void start()
  {
    if(m_type){
       do_read_header();
    }else {
      room_.join(shared_from_this());
      do_read_header();
    }
  }

  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
  }

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_read_body()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            room_.deliver(read_msg_);
            do_read_header();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_write()
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  tcp::socket socket_;
  chat_room& room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
  bool m_type;
};

//----------------------------------------------------------------------

class chat_server
{
public:
  chat_server(boost::asio::io_context& io_context,
      const tcp::endpoint& endpoint1, const tcp::endpoint& endpoint2)
    : acceptor_1(io_context, endpoint1)
    , acceptor_2(io_context, endpoint2)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_1.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<chat_session>(std::move(socket), room_, true)->start();
          }

          do_accept();  
        });
    std::cout << "sahar\n";
    acceptor_2.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
      if (!ec)
      {
        std::make_shared<chat_session>(std::move(socket), room_, false)->start();
      }

      do_accept();
    });
  }

  tcp::acceptor acceptor_1;
  tcp::acceptor acceptor_2;
  chat_room room_;
};

//----------------------------------------------------------------------

int main()
{
  try
  {
    // if (argc < 2)
    // {
    //   std::cerr << "Usage: chat_server <port> [<port> ...]\n";
    //   return 1;
    // }

    boost::asio::io_context io_context;

    std::list<chat_server> servers;
    // for (int i = 1; i < argc; ++i)
    // {
    tcp::endpoint endpoint1(tcp::v4(), 7070); //sensor ->true
    tcp::endpoint endpoint2(tcp::v4(), 8080); // controler -> false
    servers.emplace_back(io_context, endpoint1, endpoint2);
    // }

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
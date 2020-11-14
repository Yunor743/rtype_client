/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_UDPSOCKMNGR_HPP_
#define _APP_NETWORK_UDPSOCKMNGR_HPP_

#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "app/network/protocol.hpp"
#include "app/views/home/widgets/console.hpp"

using boost::asio::ip::udp;

namespace network {
    class UdpSockMngr {
        Console &console;
        boost::asio::io_context context;
        udp::socket socket;
        udp::resolver resolver;
        udp::endpoint endpoint;
        std::vector<protocol::MessageReceived<UdpCode>> received_messages;
        std::thread run_thread;
        void do_receive();
    public:
        UdpSockMngr(Console &console, const std::string &ip, short port);
        ~UdpSockMngr();
        void send(protocol::MessageToSend<UdpCode> message);
        std::vector<protocol::MessageReceived<UdpCode>> receive();
    };
}

#endif
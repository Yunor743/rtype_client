/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_TCPSOCKMNGR_HPP_
#define _APP_NETWORK_TCPSOCKMNGR_HPP_

#include <thread>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <SFML/System/Clock.hpp>
#include "app/views/home/widgets/console.hpp"
#include "app/network/protocol.hpp"
#include "app/network/asset.hpp"

using boost::asio::ip::tcp;
using boost::property_tree::ptree;
using boost::property_tree::read_json;

namespace network {
    class TcpSockMngr {
        bool is_download_finish = false;
        bool is_connection_failed = false;
        Console &console;
        std::string ip;
        short port;
        boost::asio::io_context context;
        tcp::socket socket;
        tcp::resolver resolver;
        tcp::endpoint endpoint;
        std::vector<std::pair<long, bool>> assets_ids_list;
        std::vector<Asset> assets;
        std::thread run_thread;
        sf::Clock &timeout_clock;
        long receiveAsset();
        void do_receive();
        void send(protocol::MessageToSend<TcpCode> message);
//        void do_send(protocol::MessageToSend<TcpCode> message);
        void downloadAsset(long asset_id);
        void downloadAllAssets();
    public:
        TcpSockMngr(sf::Clock &timeout, Console &console, const std::string &ip, short port, std::vector<std::pair<long, bool>>);
        ~TcpSockMngr();
        [[nodiscard]] bool isDownloadFinished() const;
        [[nodiscard]] bool isConnectionFailed() const;
        [[nodiscard]] std::vector<Asset> getAssets() const;
    };
}

#endif
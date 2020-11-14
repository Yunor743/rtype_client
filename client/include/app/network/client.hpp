/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_CLIENT_HPP_
#define _APP_NETWORK_CLIENT_HPP_

#include <memory>
#include <functional>
#include <vector>
#include <utility>
#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "sdk/managers/inputs.hpp"
#include "app/views/home/widgets/console.hpp"
#include "app/network/protocol.hpp"
#include "app/network/udpsockmngr.hpp"
#include "app/network/tcpsockmngr.hpp"
#include "app/network/asset.hpp"

namespace network {
    class Client {
        enum class Status {
            NotConnected,
            AskForAssets,
            WaitingForAssets,
            DownloadAssets,
            Ready,
            Play
        } status = Status::NotConnected;
        std::string server_ip;
        short server_udp_port;
        short server_tcp_port;
        std::vector<std::pair<long, bool>> assets_ids_list;
        std::vector<Asset> assets;
        std::unique_ptr<network::UdpSockMngr> udp = nullptr;
        std::unique_ptr<network::TcpSockMngr> tcp = nullptr;
        sf::Clock timeout_clock;
        static constexpr auto timeout = 60000;
        std::function<void(void)> onDisconnect_hdl = nullptr;
        Console *console = nullptr;
        std::vector<sf::Sprite> sprites;
        void statePlay();
        void stateAskForAssets();
        void stateWaitingForAssets();
        void stateDownload();
        void stateReady();
        void stateTimeout();
    public:
        void update();
        void setConsole(Console *new_console);
        void set_onDisconnect(std::function<void(void)> functor);
        void connect(const std::string &new_udp_server_address);
        void disconnect();
        void reset();
        [[nodiscard]] std::vector<sf::Sprite> getSprites();
    private:
        void stopSockManagers();
    };
}

#endif

/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <algorithm>
#include <cstring>
#include <utility>
#include "app/network/client.hpp"

void network::Client::statePlay()
{
    auto message_list = udp->receive();
    if (message_list.empty())
        return;
    for (auto &message : message_list) {
        // handle server disconnection
        if (message.head().code == UdpCode::Disconnect) {
            if (console) console->log("Server is disconnected");
            disconnect();
        }
        // handle server game instruction
        if (message.head().code == UdpCode::Sprite) {
            protocol::udp::from_server::Sprite sprite;
            std::memcpy(&sprite, message.body().data(), message.body().size());
            auto it = std::find_if(assets.begin(), assets.end(), [&](const auto &item){
                if (item.type != Asset::Type::Texture)
                    return false;
                if (item.id_asset != sprite.id_asset)
                    return false;
                if (item.id_tile != sprite.id_sprite)
                    return false;
                return true;
            });
            if (it != assets.end()) {
                it->sprite.setRotation(sprite.rot.x);
                it->sprite.setPosition(sprite.pos.x, sprite.pos.y);
                it->sprite.setScale(sprite.scale.x, sprite.scale.y);
                sprites.push_back(it->sprite);
            } else
                console->log("Error [Play]: Sprite specified not found");
        }
        if (message.head().code == UdpCode::Sound) {
            protocol::udp::from_server::Sound sound;
            std::memcpy(&sound, message.body().data(), message.body().size());
            auto it = std::find_if(assets.begin(), assets.end(), [&](const auto &item){
                if (item.type != Asset::Type::Sound)
                    return false;
                if (item.id_asset != sound.id)
                    return false;
                return true;
            });
            if (it != assets.end()) {
                it->sound.setPitch(sound.pitch);
                it->sound.setLoop(sound.isLooping);
                it->sound.play();
            } else
                console->log("Error [Play]: Sound specified not found");
        }
    }
    // send input
    protocol::MessageToSend<UdpCode> message;
    protocol::udp::from_client::Input body_input;
    auto mouse = Input::getMouse();
    auto keys = Input::getKeysQueue();
    body_input.pos = {static_cast<short>(mouse.x), static_cast<short>(mouse.y)};
    for (auto i = 0; i < keys.size; ++i) {
        body_input.keys[i].key = static_cast<protocol::input::Keys>(keys.data[i].key);
        body_input.keys[i].pressed = keys.data[i].pressed;
    }
    body_input.nb_keys = keys.size;
    message.head.code = protocol::udp::Code::Input;
    auto keys_size = static_cast<std::uint32_t>(sizeof(protocol::input::KeysEvent) * body_input.keys.size());
    message.head.body_size = sizeof(body_input.nb_keys) + keys_size + sizeof(body_input.pos);
    message.body.resize(message.head.body_size);
    auto offset = 0;
    std::memcpy(message.body.data(), &body_input.nb_keys, sizeof(body_input.nb_keys));
    offset += sizeof(body_input.nb_keys);
    std::memcpy(message.body.data() + offset, body_input.keys.data(), keys_size);
    offset += keys_size;
    std::memcpy(message.body.data() + offset, &body_input.pos, sizeof(body_input.pos));
    udp->send(std::move(message));
}

void network::Client::stateAskForAssets()
{
    protocol::MessageToSend<UdpCode> message;
    message.head.code = protocol::udp::Code::AskAssetList;
    message.head.body_size = 0;
    udp->send(message);
    status = Status::WaitingForAssets;
    timeout_clock.restart();
    if (console) console->log("Success [AskForAssets]");
}

void network::Client::stateWaitingForAssets()
{
    auto message_list = udp->receive();
    if (!message_list.empty()) {
        for (auto &message : message_list) {
            if (message.head().code == UdpCode::AssetList) {
                protocol::udp::from_server::AssetList assetlist;
                auto body = message.body();
                std::memcpy(&assetlist.port, body.data(), sizeof(assetlist.port));
                body += sizeof(assetlist.port);
                std::memcpy(&assetlist.size, body.data(), sizeof(assetlist.size));
                body += sizeof(assetlist.size);
                assetlist.list.resize(assetlist.size);
                std::memcpy(assetlist.list.data(), body.data(),assetlist.size * sizeof(assetlist.list.front()));
                server_tcp_port = static_cast<short>(assetlist.port);
                for (auto i = 0; i < assetlist.size; ++i)
                    assets_ids_list.emplace_back(assetlist.list[i], false);
                status = Status::DownloadAssets;
                timeout_clock.restart();
                if (console) console->log("Success [WaitingForAssets]");
                break;
            } else {
                if (console) console->log("Error [WaitingForAssets] : Server sent wrong data");
                continue;
            }
        }
    }
}

void network::Client::stateDownload()
{
    if (!tcp) {
        if (console) console->log("Start [DownloadAssets]");
        tcp = std::make_unique<network::TcpSockMngr>(timeout_clock, *console, server_ip, server_tcp_port, assets_ids_list);
    }
    if (tcp->isConnectionFailed()) {
        tcp.reset();
        if (console) console->log("[TCP] Error : connection failed");
        disconnect();
        return;
    }
    if (tcp->isDownloadFinished()) {
        assets = tcp->getAssets();
        // connect sprite to text and sound to buffer
        for (auto &asset : assets) {
            if (asset.type == Asset::Type::Sound) {
                asset.sound.setBuffer(asset.sound_buffer);
            } else if (asset.type == Asset::Type::Texture) {
                asset.sprite.setTexture(asset.texture);
                asset.sprite.setTextureRect({asset.config.origin_x, asset.config.origin_y, asset.config.width, asset.config.height});
            }
        }
        tcp.reset();
        status = Status::Ready;
        timeout_clock.restart();
        if (console) console->log("Success [DownloadAssets]");
    }
}

void network::Client::stateReady()
{
    protocol::MessageToSend<UdpCode> message;
    message.head.code = protocol::udp::Code::Ready;
    message.head.body_size = 0;
    udp->send(message);
    status = Status::Play;
    timeout_clock.restart();
    if (console) console->log("Success [Ready]");
}

void network::Client::stateTimeout()
{
    if (console) console->log("Error : Timed out");
    disconnect();
}

void network::Client::update()
{
    switch (status) {
        case Status::NotConnected:
            return;
        case Status::Play:
            statePlay();
            return;
        case Status::AskForAssets:
            stateAskForAssets();
            break;
        case Status::WaitingForAssets:
            stateWaitingForAssets();
            break;
        case Status::DownloadAssets:
            stateDownload();
            break;
        case Status::Ready:
            stateReady();
            break;
        default: break;
    }
    if (timeout_clock.getElapsedTime().asMilliseconds() >= timeout) {
        stateTimeout();
    }
}

void network::Client::setConsole(Console *new_console)
{
    console = new_console;
}

void network::Client::set_onDisconnect(std::function<void(void)> functor)
{
    onDisconnect_hdl = std::move(functor);
}

static std::optional<std::pair<std::string, short>> parseAddress(const std::string &address)
{
    std::pair<std::string, short> ret;
    auto index = address.find_last_of(':');
    if (index == std::string::npos)
        return std::nullopt;
    ret.first = address.substr(0, index);
    ret.second = std::stoi(address.data() + index + 1);
    return std::optional(ret);
}

void network::Client::connect(const std::string &new_udp_server_address)
{
    auto host = parseAddress(new_udp_server_address);
    if (host == std::nullopt) {
        if (console) console->log( "failed to parse address");
        disconnect();
        return;
    }
    server_ip = host.value().first;
    server_udp_port = host.value().second;
    if (console) console->log( "try to connect to : " + server_ip + ":" + std::to_string(server_udp_port));
    udp = std::make_unique<network::UdpSockMngr>(*console, server_ip, server_udp_port);
    if (udp)
        status = Status::AskForAssets;
    timeout_clock.restart();
}

void network::Client::disconnect()
{
    stopSockManagers();
    status = Status::NotConnected;
    timeout_clock.restart();
    onDisconnect_hdl();
    if (console) console->log("you have been disconnected");
    reset();
}

void network::Client::reset()
{
    server_ip.clear();
    server_udp_port = 0;
    server_tcp_port = 0;
    assets_ids_list.clear();
}

std::vector<sf::Sprite> network::Client::getSprites()
{
    return std::move(sprites);
}

void network::Client::stopSockManagers()
{
    if (udp)
        udp.reset();
    if (tcp)
        tcp.reset();
}




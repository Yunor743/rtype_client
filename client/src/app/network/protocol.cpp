/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/protocol.hpp"

bool protocol::check_size(UdpCode type, uint32_t size) {
    if (type == UdpCode::Sprite) return size == sizeof(protocol::udp::from_server::Sprite);
    if (type == UdpCode::Sound) return size == sizeof(protocol::udp::from_server::Sound);
    if (type == UdpCode::AssetList) return size >= sizeof(protocol::udp::from_server::AssetList::port) + sizeof(protocol::udp::from_server::AssetList::size);;
    if (type == UdpCode::AskAssetList) return size == 0;
    if (type == UdpCode::Ready) return size == 0;
    if (type == UdpCode::Input) return size == sizeof(protocol::udp::from_client::Input);
    if (type == UdpCode::Disconnect) return size == 0;
    return false;
}

bool protocol::check_size(TcpCode type, uint32_t size) {
    if (type == TcpCode::AssetAsk) return size == sizeof(protocol::tcp::AssetAsk);
    if (type == TcpCode::AssetPackage) return size == sizeof(protocol::tcp::AssetPackage);
    return false;
}
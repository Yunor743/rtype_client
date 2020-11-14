/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_PROTOCOL_HPP_
#define _SDK_PROTOCOL_HPP_

#include <cstddef>
#include <array>
#include <type_traits>
#include <vector>
#include <cstring>
#include <boost/asio/buffer.hpp>

namespace protocol {
    namespace transform {
        struct Rotation {
            float x;
            float y;
        };
        struct Position {
            float x;
            float y;
        };
        struct Scale {
            float x;
            float y;
        };
    }
    namespace input {
        constexpr short keys_array_size = 5;
        enum class Keys {
            LeftClick = 1,
            RightClick,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            Escape,
            LControl,
            LShift,
            LAlt,
            RControl,
            RShift,
            RAlt,
            Tab,
            Space,
            Enter,
            BackSpace,
            Left,
            Right,
            Up,
            Down,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15
        };
        struct KeysEvent {
            bool pressed: 1;
            Keys key: 7;
        };
        struct MousePos {
            short y;
            short x;
        };
    }
    constexpr std::pair<std::byte, std::byte> magic_number = {std::byte{0xFA}, std::byte{0xDA}};
    namespace udp {
        // UDP code
        enum class Code : uint8_t {
            Sprite = 1,         // from server
            Sound = 2,          // from server
            AssetList = 3,      // from server
            AskAssetList = 4,   // from client
            Ready = 5,          // from client
            Input = 6,          // from client
            Disconnect = 7,     // Both
        };
        namespace from_server {
            struct Sprite {
                long id_asset;     // the tilesheet
                long id_sprite;    // the sprite id of the tilesheet
                transform::Rotation rot;
                transform::Position pos;
                transform::Scale scale;
            };
            struct Sound {
                long id;
                float pitch;
                bool isLooping;
            };
            struct AssetList {
                unsigned port;          // port of the tcp server (same ip)
                std::size_t size;       // size of list
                std::vector<long> list; // list of asset ids
            };
        }
        namespace from_client {
            struct AskAssetList {};     // ask the server a list of ids representing all game assets
            struct Ready {};            // indicate at the server that all asset are loaded and the client is ready to play
            struct Input {              // return to the server all user inputs (mouse & keyboard)
                short nb_keys = 0;
                std::array<input::KeysEvent, input::keys_array_size> keys;
                input::MousePos pos;
            };
        }
        struct Disconnect {};
    }
    namespace tcp {
        // TCP code
        enum class Code : uint8_t {
            AssetAsk = 1,       // from client
            AssetPackage = 2    // from server
        };
        struct AssetAsk {
            long id;
        };
        struct AssetPackage {
            enum class Type {
                Sound = 1,
                Texture = 2
            } type;
            long id_asset;
            std::size_t size_data;
            std::size_t size_config;
            /**
             * Raw data of the asset (Sound or Texture)
             */
            std::vector<std::byte> data;
            /**
             * json : use it only if type == Texture | define how an image has to be cut in sprites
             */
            std::vector<std::byte> config;
        };
    }
    template<typename T>
    struct MessageHeader {
        std::byte firstbyte = protocol::magic_number.first;
        std::byte secondbyte = protocol::magic_number.second;
        T code;
        uint32_t body_size;     // security : must be equal as sizeof(type defined by code)
    };
    template<typename T>
    class MessageReceived {
        std::vector<std::byte> data;
    public:
        explicit MessageReceived(std::vector<std::byte> data) : data(std::move(data)) {}
        MessageHeader<T> head() const {
            MessageHeader<T> ret;
            std::memcpy(&ret, data.data(), sizeof(ret));
            return ret;
        }
        boost::asio::const_buffer body() const {
            return {data.data() + sizeof(head()), head().body_size};
        }
    };
    template<typename T>
    struct MessageToSend {
        MessageHeader<T> head;
        std::vector<std::byte> body;
    };
}

using UdpCode = protocol::udp::Code;
using TcpCode = protocol::tcp::Code;

namespace protocol {
    bool check_size(UdpCode type, uint32_t size);
    bool check_size(TcpCode type, uint32_t size);
}

#endif

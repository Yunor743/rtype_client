#include <array>
#include <unordered_map>
#include <unordered_set>

#ifndef _GAMESERVER_HPP_
#define _GAMESERVER_HPP_

#include "Storage.hpp"
#include "Modules.hpp"
#include "interface/UdpServer.hpp"
#include "AssetsServer.hpp"

struct Player {
    bool ready = false;
    short nb_key = 0;
    std::unordered_set<protocol::udp::keys::Keys> keys;
    std::vector<protocol::udp::keys::Keys> input;
    Dimensional cur_pos = {0, 0};
};

class GameServer:
    public ecs::udp::Server<protocol::udp::RequestCode>,
    public IAudioModule,
    public IDisplayModule,
    public IInputModule
{
    public:
        GameServer(unsigned port, std::filesystem::path &p);
        ~GameServer();

        // Required by IModule
        virtual void update()final;

        // Required by ecs::udp::Server
        virtual void onMessage(Message<protocol::udp::RequestCode> msg)final;

        // Required by IAudioModule
        virtual void playSound(const std::string &name, float volume, float pitch)final;

        // Required by IDisplayModule
        virtual void drawSprite(const std::string &name, Transform const &transf, unsigned tile_id)final;

        // Required by IInputModule
        virtual Dimensional getCursorLocation(const unsigned player)final;
        virtual std::vector<Input> getInputEvents(const unsigned player)final;
        virtual bool isKeyPressed(unsigned player, Input key)final;

    private:
        AssetsServer assets;
        std::shared_ptr<Storage> stor;
        std::unordered_map<std::shared_ptr<ecs::IClient<protocol::udp::RequestCode>>, Player> list;
        std::string path;
        unsigned port;
};

#endif //_GAMESERVER_HPP_

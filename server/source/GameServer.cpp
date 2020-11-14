#include "GameServer.hpp"
#include "Snitch.hpp"

using namespace protocol::udp;

GameServer::GameServer(unsigned port, std::filesystem::path &p) :
    Server(port), assets(port + 1, p), port(port)
{
    this->stor = this->assets.getStorage();
    this->start();
};

GameServer::~GameServer()
{
    Message<RequestCode> msg;
    msg.head.code = RequestCode::Disconnect;
    this->msgAll(msg);
};

void GameServer::update() {
    this->Server::update();
}

void GameServer::onMessage(Message<RequestCode> msg) {
    Snitch::msg("GAME_SERVER") << msg << Snitch::endl;
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        if (!list.contains(msg.remote)) { list.insert({msg.remote, Player{}}); }
        switch (msg.head.code) {
        case RequestCode::Disconnect: msg.remote->disconnect(); break;
        case RequestCode::Ready: list.at(msg.remote).ready = true; break;
        case RequestCode::Input: {
            auto body = reinterpret_cast<protocol::udp::Input *>(msg.body.data());
            if (!body) { break; }
            list.at(msg.remote).nb_key = std::move(body->nb_keys);
            for (const auto &i : body->keys ) {
                list.at(msg.remote).input.push_back(i.key);
                if (i.pressed)
                    list.at(msg.remote).keys.insert(i.key);
                else
                    list.at(msg.remote).keys.erase(i.key);
            }
            list.at(msg.remote).cur_pos.y = std::move(body->pos.y);
            list.at(msg.remote).cur_pos.x = std::move(body->pos.x);
        } break;
        case RequestCode::AssetsAsk: {
            Message<RequestCode> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
            rep.head.code = RequestCode::AssetsList;
            protocol::udp::AssetsList ass;
            ass.port = port + 1;
            for (const auto &[_, e]: stor->getStorage()) {
                ass.list.push_back(e);
            }
            ass.size = ass.list.size();
            rep.insert(ass);
            msg.remote->send(rep);
            Snitch::msg("GAME_SERVER") << "Replied RequestCode::AssetsList" << Snitch::endl;
        } break;
        default: Snitch::warn("GAME_SERVER") << "Unkown comand" << Snitch::endl; break;
        }
    }
}

void GameServer::playSound(const std::string &name, float volume, float pitch) {
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
    Message<RequestCode> rep;
    rep.head.code = protocol::udp::RequestCode::Sound;
    protocol::udp::Sound s;
    s.volume = volume;
    s.pitch = pitch;
    s.isLooping = false;
    auto v = stor->getIdFromPath(name);
    s.id = v ? *v : -1;
    rep.insert(s);
    this->msgAll(rep);
}

void GameServer::drawSprite(const std::string &name, const Transform &transf, unsigned int tile_id) {
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
    Message<RequestCode> rep;
    rep.head.code = protocol::udp::RequestCode::Sound;
    protocol::udp::Sprite s;
    s.rot.x = transf.rotation.x;
    s.rot.y = transf.rotation.y;
    s.pos.x = transf.location.x;
    s.pos.y = transf.location.y;
    s.scale.x = transf.scale.x;
    s.scale.y = transf.scale.y;
    auto v = stor->getIdFromPath(name);
    s.id_assets = v ? *v : -1;
    s.id_rectangle = tile_id;
    rep.insert(s);
    this->msgAll(rep);
}

Dimensional GameServer::getCursorLocation(const unsigned player) {
    for (const auto &[e, i] : list) {
        if (e->getId() == player && i.ready) {
            return i.cur_pos;
        }
    }
    return Dimensional {-1, -1};
}

std::vector<::Input> GameServer::getInputEvents(const unsigned player) {
    for (auto &[e, i] : list) {
        if (e->getId() == player && i.ready) {
            std::vector<::Input> ret = i.input;
            i.input.clear();
            return ret;
        }
    }
    return std::vector<::Input>();
}

bool GameServer::isKeyPressed(unsigned player, ::Input key) {
    for (const auto &[e, i]: list) {
        if (e->getId() == player && i.ready) {
            return i.keys.contains(key);
        }
    }
    return false;
}

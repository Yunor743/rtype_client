#include <fstream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <filesystem>

#include "AssetsServer.hpp"
#include "Snitch.hpp"

const std::unordered_map<std::string, protocol::tcp::AssetsPackage::Type> ext_to_type {
    {".png", protocol::tcp::AssetsPackage::Texture},
    {".gif", protocol::tcp::AssetsPackage::Texture},
    {".mp3", protocol::tcp::AssetsPackage::Sound}
};

AssetsServer::AssetsServer(const unsigned port, const std::string &path):
    Server(port), stor(std::make_shared<Storage>(path, [](std::filesystem::path p) {
        if (!ext_to_type.contains(p.extension()))
            return false;
        return true;
    }))
{
    for (auto &[i, e]: stor->getStorage()) {
        if (!ext_to_type.contains(std::filesystem::path(i).extension()))
            continue;
        assets_map.insert({e, ext_to_type.at(std::filesystem::path(i).extension())});
    }
    this->start();
};

AssetsServer::~AssetsServer()
{
    this->stop();
}

void AssetsServer::onMessage(Message<protocol::tcp::AssetsRequest> msg) {
    Message<protocol::tcp::AssetsRequest> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        switch (msg.head.code) {
            case protocol::tcp::AssetsRequest::AskAssets: {
                auto body = reinterpret_cast<protocol::tcp::AssetsAsk *>(msg.body.data());
                protocol::tcp::AssetsPackage reply;
                try {
                    auto path_data = stor->getPathFromId(body->id);
                    if (!path_data)
                        break;
                    reply.data = this->getFileAt(*path_data);
                    reply.config = this->getFileAt(this->getConfigForAssets(*path_data));
                    if (reply.data.size() != 0 && reply.config.size() != 0) {
                        reply.size_data = reply.data.size();
                        reply.size_config = reply.config.size();
                        reply.id = body->id;
                        reply.type = assets_map.at(body->id);
                        rep.head.code = msg.head.code;
                        rep.insert(reply);
                    }
                } catch (const std::runtime_error &re) {
                    Snitch::warn("ASSETS_SERVER") << "Execption " << re.what() << Snitch::endl;
                }
            } break;
            default: break;
        }
    }
    msg.remote->send(rep);
}

std::shared_ptr<Storage> AssetsServer::getStorage()const {
    return stor;
}

std::vector<uint8_t> AssetsServer::getFileAt(const std::string &path) {
    std::vector<uint8_t> ret;
    std::ifstream file;
    file.open(path);
    if (file.is_open()) {
        file >> std::noskipws;
        std::copy(std::istream_iterator<uint8_t>(file),
                  std::istream_iterator<uint8_t>(),
                  std::back_inserter(ret));
        file.close();
    }
    return ret;
}

std::string AssetsServer::getConfigForAssets(std::string path) {
    size_t dot = path.find_last_of('.');
    if (dot == std::string::npos)
        throw std::runtime_error("not dot");
    path.replace(dot, 5, ".json");
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Not a valid path");
    }
    return path;
}

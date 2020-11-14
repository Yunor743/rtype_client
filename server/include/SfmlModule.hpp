#ifndef SFML_MODULE_HPP
#define SFML_MODULE_HPP

#include "Modules.hpp"
#include "components/Transform.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <memory>

class SfmlModule : public IDisplayModule, public IInputModule {
    sf::RenderWindow m_window;
    std::vector<Input> m_pending_inputs;
    std::filesystem::path m_assets_path;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    std::unordered_map<std::string, std::unordered_map<unsigned, sf::Sprite>> m_sprites;

    void retrieveInputs();
    void loadAsset(std::filesystem::path path);
public:
    SfmlModule(const std::string &name, std::filesystem::path assets_path);
    void drawSprite(const std::string &name, Transform const &transform, unsigned id) override;
    void drawDebugBox(sf::RectangleShape box);
    void update() override;
    std::vector<Input> getInputEvents(unsigned player) override;
    Dimensional getCursorLocation(unsigned player) override;
    bool isKeyPressed(unsigned player, Input key) override;
    ~SfmlModule();
};

#endif

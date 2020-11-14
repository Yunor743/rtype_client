#include "SfmlModule.hpp"
#include "SfmlKeyMapping.hpp"
#include "Snitch.hpp"
#include <iostream>
#include <string_view>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <cstdlib>


SfmlModule::SfmlModule(const std::string &name, std::filesystem::path assets_path)
: m_window(sf::VideoMode(1800, 900), name), m_assets_path(assets_path)
{
    for (auto &file : std::filesystem::directory_iterator(m_assets_path)) {
        if (file.path().string().ends_with(".png"))
            loadAsset(file.path());
    }
}

void SfmlModule::loadAsset(std::filesystem::path path)
{
    // Loading Texture raw asset

    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    (*texture).loadFromFile(path);

    // Loading Spritesheet configuration file

    boost::property_tree::ptree root(m_assets_path);
    std::cout << "Parsing " << path.replace_extension(".json") << std::endl;
    boost::property_tree::read_json(path.replace_extension(".json"), root);

    // Creating Sprites from configuration

    m_sprites[path.stem()] = {};
    for (auto const &sprite : root.get_child("sprites")) {
        sf::Sprite new_sprite(*texture);
        sf::Rect<int> texture_rect(
            sprite.second.get<int>("origin_x"),
            sprite.second.get<int>("origin_y"),
            sprite.second.get<int>("width"),
            sprite.second.get<int>("height")
        );

        new_sprite.setTextureRect(texture_rect);
        m_sprites.at(path.stem())
        .emplace(sprite.second.get<int>("id"), std::move(new_sprite));
    }

    // Storing texture

    m_textures.emplace(path.stem(), std::move(texture));

    std::cout << "Loaded " << path.stem() << std::endl;
}

void SfmlModule::drawSprite(const std::string &name, Transform const &transform, unsigned id)
{
    sf::Sprite &sprite = m_sprites.at(name).at(id);

    sprite.setPosition(transform.location.x, transform.location.y);
    sprite.setRotation(transform.rotation.x);
    sprite.setScale(transform.scale.x, transform.scale.y);

    m_window.draw(sprite);
}

void SfmlModule::drawDebugBox(sf::RectangleShape box)
{
    box.setFillColor(sf::Color(255, 0, 0, 100));
    m_window.draw(box);
}

void SfmlModule::update()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Snitch::warn() << "Oh naw, you stopped the game the wrong way :/" << Snitch::endl;
            /*
            ** exit is actually an alias for a well designed function
            ** that correctly handles the game's stop and absolutely not
            ** a simple exit
            */
            exit(0);
        }
    }
    m_window.display();
    m_window.clear();
}

std::vector<Input> SfmlModule::getInputEvents(unsigned player)
{
    std::vector<Input> inputs;

    std::swap(inputs, m_pending_inputs);

    return inputs;
}

Dimensional SfmlModule::getCursorLocation(unsigned player)
{
    sf::Vector2i position = sf::Mouse::getPosition();

    return Dimensional{static_cast<float>(position.x),
                       static_cast<float>(position.y)};
}

bool SfmlModule::isKeyPressed(unsigned player, Input key)
{
    sf::Keyboard::Key sfml_key =
        SfmlKeyMapping::rtype_key_mapping[static_cast<std::size_t>(key)];

    if (sfml_key != sf::Keyboard::Unknown)
        return sf::Keyboard::isKeyPressed(sfml_key);
    else
        return false;
}

void SfmlModule::retrieveInputs()
{
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_pending_inputs.push_back(Input::ExitWindow);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Button::Left)
                m_pending_inputs.push_back(Input::LeftClick);
            if (event.mouseButton.button == sf::Mouse::Button::Right)
                m_pending_inputs.push_back(Input::RightClick);
        }
        if (event.type == sf::Event::KeyPressed)
            m_pending_inputs.push_back(
                SfmlKeyMapping::sfml_key_mapping[event.key.code]);
    }
}

SfmlModule::~SfmlModule()
{
    m_window.close();
}

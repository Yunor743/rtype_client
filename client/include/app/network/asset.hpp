/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_ASSET_HPP_
#define _APP_NETWORK_ASSET_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct SpriteConfig {
    int id;
    int origin_x;
    int origin_y;
    int width;
    int height;
};

struct Asset {
    enum class Type {
        Sound = 1,
        Texture = 2,
    } type;
    long id_asset;
    long id_tile;                  // if type is texture
    sf::Texture texture;           // if type is texture
    sf::Sprite sprite;             // if type is texture
    SpriteConfig config;           // if type is texture
    sf::Sound sound;               // if type is Sound
    sf::SoundBuffer sound_buffer;  // if type is Sound
};

#endif
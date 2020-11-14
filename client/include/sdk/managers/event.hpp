/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_MANAGERS_EVENTS_H_
#define _SDK_MANAGERS_EVENTS_H_

#include <array>
#include <map>
#include <SFML/Graphics.hpp>
#include "sdk/structures/keyboard.hpp"

namespace event {
    constexpr auto KEYSARRAYSIZE = 255;

    struct KeyEvent {
        bool pressed: 1;
        keyboard::Key key: 7;
    };
}

class Event {
    sf::RenderWindow &window;
    sf::Event event;
public:
    std::string text_entered;
    std::map<keyboard::Key, keyboard::KeyStatus> keys_state;
    /**
     * A FIFO queue for Key event
     */
    struct KeysEvent {
        std::array<event::KeyEvent, event::KEYSARRAYSIZE> data;
        unsigned char size;
    } keys_event;
    sf::Vector2<int> mouse;
    explicit Event(sf::RenderWindow &window);
    void update();
};

#endif
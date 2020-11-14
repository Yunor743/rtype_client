/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <optional>
#include "sdk/managers/event.hpp"

Event::Event(sf::RenderWindow &sf_win) : window(sf_win)
{
    for (auto i = 0; i < keyboard::NB_KEYS; ++i) {
        keys_state.emplace(static_cast<keyboard::Key>(i), keyboard::KeyStatus::RELEASED);
    }
    keys_event.size = 0;
    mouse = {0, 0};
}

static std::optional<keyboard::Key> do_sfml_relation(sf::Keyboard::Key sfml_key)
{
    const auto item = std::find_if(keyboard::relation_sfml.begin(), keyboard::relation_sfml.end(), [&](const auto &pair) {
        return pair.second == sfml_key;
    });
    if (item == keyboard::relation_sfml.end())
        return std::nullopt;
    return std::optional<keyboard::Key>(item->first);
}

static void add_to_queue(Event *event, keyboard::Key key, keyboard::KeyStatus status)
{
    // delete last elem if queue is full
    if (event->keys_event.size == event::KEYSARRAYSIZE)
        --event->keys_event.size;
    // shift all elems to 1 at right
    for (auto i = 0; i < event->keys_event.size; ++i)
        event->keys_event.data[i + 1] = event->keys_event.data[i];
    // add new elem
    event->keys_event.data[0].pressed = (status == keyboard::KeyStatus::PRESSED);
    event->keys_event.data[0].key = key;
    ++event->keys_event.size;
}

void Event::update()
{
    keys_event.size = 0;
    text_entered.clear();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::TextEntered) {
            text_entered += event.text.unicode;
        }
        if (event.type == sf::Event::KeyPressed) {
            const auto key = do_sfml_relation(event.key.code);
            if (key != std::nullopt) {
                if (keys_state.at(key.value()) != keyboard::KeyStatus::PRESSED) {
                    keys_state.at(key.value()) = keyboard::KeyStatus::PRESSED;
                    add_to_queue(this, key.value(), keyboard::KeyStatus::PRESSED);
                }
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            const auto key = do_sfml_relation(event.key.code);
            if (key != std::nullopt) {
                if (keys_state.at(key.value()) != keyboard::KeyStatus::RELEASED) {
                    keys_state.at(key.value()) = keyboard::KeyStatus::RELEASED;
                    add_to_queue(this, key.value(), keyboard::KeyStatus::RELEASED);
                }
            }
        }
        // Mouse btn
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && keys_state.at(keyboard::Key::LeftClick) != keyboard::KeyStatus::PRESSED) {
                keys_state.at(keyboard::Key::LeftClick) = keyboard::KeyStatus::PRESSED;
                add_to_queue(this, keyboard::Key::LeftClick, keyboard::KeyStatus::PRESSED);
            }
            if (event.mouseButton.button == sf::Mouse::Right && keys_state.at(keyboard::Key::RightClick) != keyboard::KeyStatus::PRESSED) {
                keys_state.at(keyboard::Key::RightClick) = keyboard::KeyStatus::PRESSED;
                add_to_queue(this, keyboard::Key::RightClick, keyboard::KeyStatus::PRESSED);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && keys_state.at(keyboard::Key::LeftClick) != keyboard::KeyStatus::RELEASED) {
                keys_state.at(keyboard::Key::LeftClick) = keyboard::KeyStatus::RELEASED;
                add_to_queue(this, keyboard::Key::LeftClick, keyboard::KeyStatus::RELEASED);
            }
            if (event.mouseButton.button == sf::Mouse::Right && keys_state.at(keyboard::Key::RightClick) != keyboard::KeyStatus::RELEASED) {
                keys_state.at(keyboard::Key::RightClick) = keyboard::KeyStatus::RELEASED;
                add_to_queue(this, keyboard::Key::RightClick, keyboard::KeyStatus::RELEASED);
            }
        }
    }
    mouse = sf::Mouse::getPosition(window);
}



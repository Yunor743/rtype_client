#ifndef RTYPE_SFMLKEYMAPPING_H_
#define RTYPE_SFMLKEYMAPPING_H_

#include "Modules.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <array>

namespace SfmlKeyMapping
{
    constexpr std::initializer_list<std::pair<sf::Keyboard::Key, Input>>
        internal_sfml_mapping = {
            {sf::Keyboard::Key::A, Input::A},
            {sf::Keyboard::Key::B, Input::B},
            {sf::Keyboard::Key::C, Input::C},
            {sf::Keyboard::Key::D, Input::D},
            {sf::Keyboard::Key::E, Input::E},
            {sf::Keyboard::Key::F, Input::F},
            {sf::Keyboard::Key::G, Input::G},
            {sf::Keyboard::Key::H, Input::H},
            {sf::Keyboard::Key::I, Input::I},
            {sf::Keyboard::Key::J, Input::J},
            {sf::Keyboard::Key::K, Input::K},
            {sf::Keyboard::Key::L, Input::L},
            {sf::Keyboard::Key::M, Input::M},
            {sf::Keyboard::Key::N, Input::N},
            {sf::Keyboard::Key::O, Input::O},
            {sf::Keyboard::Key::P, Input::P},
            {sf::Keyboard::Key::Q, Input::Q},
            {sf::Keyboard::Key::R, Input::R},
            {sf::Keyboard::Key::S, Input::S},
            {sf::Keyboard::Key::T, Input::T},
            {sf::Keyboard::Key::U, Input::U},
            {sf::Keyboard::Key::V, Input::V},
            {sf::Keyboard::Key::W, Input::W},
            {sf::Keyboard::Key::X, Input::X},
            {sf::Keyboard::Key::Y, Input::Y},
            {sf::Keyboard::Key::Z, Input::Z},
            {sf::Keyboard::Key::Num0, Input::Num0},
            {sf::Keyboard::Key::Num1, Input::Num1},
            {sf::Keyboard::Key::Num2, Input::Num2},
            {sf::Keyboard::Key::Num3, Input::Num3},
            {sf::Keyboard::Key::Num4, Input::Num4},
            {sf::Keyboard::Key::Num5, Input::Num5},
            {sf::Keyboard::Key::Num6, Input::Num6},
            {sf::Keyboard::Key::Num7, Input::Num7},
            {sf::Keyboard::Key::Num8, Input::Num8},
            {sf::Keyboard::Key::Num9, Input::Num9},
            {sf::Keyboard::Key::Escape, Input::Escape},
            {sf::Keyboard::Key::LControl, Input::LControl},
            {sf::Keyboard::Key::LShift, Input::LShift},
            {sf::Keyboard::Key::LAlt, Input::LAlt},
            {sf::Keyboard::Key::RControl, Input::RControl},
            {sf::Keyboard::Key::RShift, Input::RShift},
            {sf::Keyboard::Key::RAlt, Input::RAlt},
            {sf::Keyboard::Key::Tab, Input::Tab},
            {sf::Keyboard::Key::Space, Input::Space},
            {sf::Keyboard::Key::Enter, Input::Enter},
            {sf::Keyboard::Key::BackSpace, Input::BackSpace},
            {sf::Keyboard::Key::Left, Input::Left},
            {sf::Keyboard::Key::Right, Input::Right},
            {sf::Keyboard::Key::Up, Input::Up},
            {sf::Keyboard::Key::Down, Input::Down},
            {sf::Keyboard::Key::F1, Input::F1},
            {sf::Keyboard::Key::F2, Input::F2},
            {sf::Keyboard::Key::F3, Input::F3},
            {sf::Keyboard::Key::F4, Input::F4},
            {sf::Keyboard::Key::F5, Input::F5},
            {sf::Keyboard::Key::F6, Input::F6},
            {sf::Keyboard::Key::F7, Input::F7},
            {sf::Keyboard::Key::F8, Input::F8},
            {sf::Keyboard::Key::F9, Input::F9},
            {sf::Keyboard::Key::F10, Input::F10},
            {sf::Keyboard::Key::F11, Input::F11},
            {sf::Keyboard::Key::F12, Input::F12},
            {sf::Keyboard::Key::F13, Input::F13},
            {sf::Keyboard::Key::F14, Input::F14},
            {sf::Keyboard::Key::F15, Input::F15},
    };

    constexpr std::array<Input, sf::Keyboard::KeyCount> create_sfml_mapping()
    {

        std::array<Input, sf::Keyboard::KeyCount> mapping = {Input::Unknwown};

        for (auto [sfml_key, rtype_key] : internal_sfml_mapping) {
            mapping[sfml_key] = rtype_key;
        }
        return mapping;
    }

    constexpr std::array<Input, sf::Keyboard::KeyCount> sfml_key_mapping =
        create_sfml_mapping();

    constexpr std::size_t rtype_key_count =
        static_cast<std::size_t>(Input::KeyCount);

    constexpr std::array<sf::Keyboard::Key, rtype_key_count>
    create_rtype_mapping()
    {

        std::array<sf::Keyboard::Key, rtype_key_count> mapping = {
            sf::Keyboard::Unknown};

        for (auto [sfml_key, rtype_key] : internal_sfml_mapping) {
            mapping[static_cast<std::size_t>(rtype_key)] = sfml_key;
        }
        return mapping;
    }

    constexpr std::array<sf::Keyboard::Key, rtype_key_count> rtype_key_mapping =
        create_rtype_mapping();
} // namespace SfmlKeyMapping

#endif // RTYPE_SFMLKEYMAPPING_H_

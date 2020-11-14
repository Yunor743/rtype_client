/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_STRUCTURES_BIDIMENSIONAL_HPP_
#define _SDK_STRUCTURES_BIDIMENSIONAL_HPP_

#include <SFML/System/Vector2.hpp>

namespace bidimensional {
    struct Transform {
        sf::Vector2<float> scale;
        sf::Vector2<float> position;
    };
}

#endif
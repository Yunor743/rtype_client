/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_ICOLOR_HPP_
#define _SDK_INTERFACES_ICOLOR_HPP_

#include <map>
#include <string>
#include <optional>
#include <SFML/Graphics.hpp>

class Icolors {
protected:
    std::map<std::string, sf::Color> list;
public:
    [[nodiscard]] std::optional<sf::Color> get(const std::string &key);
};

#endif
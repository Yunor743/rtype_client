/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/interfaces/Icolors.hpp"

std::optional<sf::Color> Icolors::get(const std::string &key)
{
    auto item = list.find(key);
    if (item == list.end())
        return std::nullopt;
    return std::optional<sf::Color>(item->second);
}
/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/interfaces/Iwidget.hpp"

Iwidget::Iwidget(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window) :
    Ifragment(view_intent, parent_trans, main_window)
{}

void Iwidget::rotate(float angle)
{
    const auto actual = content.getRotation();
    content.setRotation(actual + angle);
}


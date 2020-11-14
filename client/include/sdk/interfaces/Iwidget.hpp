/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_IWIDGET_HPP_
#define _SDK_INTERFACES_IWIDGET_HPP_

#include <string>
#include <optional>
#include <SFML/Graphics.hpp>
#include "sdk/structures/bidimensional.hpp"
#include "sdk/interfaces/Ifragment.hpp"

class Iwidget : public Ifragment {

public:
    Iwidget(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window);
    /**
     * Rotate the widget
     * @param angle in degrees
     */
    void rotate(float angle);
};


#endif
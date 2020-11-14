/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_IVIEW_HPP_
#define _SDK_INTERFACES_IVIEW_HPP_

#include <optional>
#include <type_traits>
#include <vector>
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Ifragment.hpp"
#include "sdk/interfaces/Itheme.hpp"

class Iview : public Ifragment {
    bidimensional::Transform absolute;
    std::optional<std::string> intent = std::nullopt;
    using Ifragment::move;  // make inherited public function move private
protected:
    sf::RenderWindow &window;
public:
    Iview(sf::RenderWindow &main_window, sf::Vector2<float> size);
    [[nodiscard]] std::optional<std::string> get_intent();
    void runCreate() override;
    void runUpdate() override;
};

#endif
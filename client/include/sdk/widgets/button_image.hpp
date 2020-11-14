/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_BUTTON_IMAGE_HPP_
#define _SDK_WIDGETS_BUTTON_IMAGE_HPP_

#include <iostream>
#include "sdk/widgets/button_text.hpp"

class WidgetButtonImage : public WidgetButtonText {
    sf::Vector2<float> size;
    sf::Texture text;
    sf::Sprite sprite;
    using WidgetButtonText::set_text;
    using WidgetButtonText::set_font;
    using WidgetButtonText::set_fontsize;
    using WidgetButtonText::set_color;
    void onUpdateView() override;
public:
    WidgetButtonImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_image(const std::string &path);
    void set_size(sf::Vector2<float> newsize);
};

#endif
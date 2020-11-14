/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_LOADER_HPP_
#define _SDK_WIDGETS_LOADER_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/widgets/image.hpp"
#include "sdk/interfaces/Itheme.hpp"

class WidgetLoader : public Iwidget {

    WidgetImage *img = nullptr;
    float rotate_value = 0;
    sf::Clock clock;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    WidgetLoader(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_img(const std::string &path);
    void set_scale_bysize(sf::Vector2<float> size);
    void set_background(sf::Color color);
    void set_rotation(float angle);
};

#endif
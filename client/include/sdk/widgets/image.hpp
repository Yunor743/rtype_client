/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_IMAGE_HPP_
#define _SDK_WIDGETS_IMAGE_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"

class WidgetImage : public Iwidget {
    std::string image_path;
    sf::Texture texture;
    sf::Sprite sprite;
    bool use_default_size = true;
    sf::Vector2<float> size;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    void reload();
public:
    WidgetImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_img(const std::string &path);
    void set_size(sf::Vector2<float> newsize);
    void set_scale(sf::Vector2<float> newscale);
    void set_scale_bysize(sf::Vector2<float> size);
    void set_background(sf::Color);
};

#endif
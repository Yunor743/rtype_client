/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/image.hpp"

WidgetImage::WidgetImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
    background_color = theme->getColor("Transparent").value();
}

void WidgetImage::onCreateView()
{}

void WidgetImage::onUpdateView()
{
    window.draw(sprite);
}

void WidgetImage::onFinishView()
{}

void WidgetImage::reload()
{
    if (!image_path.empty()) {
        texture.loadFromFile(image_path);
        size = {static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)};
        if (use_default_size)
            transform.scale = size;
        sprite.setTexture(texture);
    }
}

void WidgetImage::set_img(const std::string &path)
{
    image_path = path;
    reload();
}

void WidgetImage::set_size(sf::Vector2<float> newsize)
{
    use_default_size = false;
    transform.scale = newsize;
    reload();
}

void WidgetImage::set_scale(sf::Vector2<float> newscale)
{
    sprite.scale(newscale);
    reload();
}

void WidgetImage::set_scale_bysize(sf::Vector2<float> newsize)
{
    const auto x = newsize.x / size.x;
    const auto y = newsize.y / size.y;
    set_scale({x, y});
    set_size(newsize);
}

void WidgetImage::set_background(sf::Color color)
{
    background_color = color;
    reload();
}





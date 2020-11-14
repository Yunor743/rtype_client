/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/loader.hpp"

WidgetLoader::WidgetLoader(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
        Iwidget(view_intent, parent_trans, main_window)
{
    background_color = theme->getColor("Transparent").value();
    add_widget<WidgetImage>("Loader_img", theme);
    img = get_fragment<WidgetImage>("Loader_img");
    clock.restart();
}

void WidgetLoader::onCreateView()
{}

void WidgetLoader::onUpdateView()
{
    if (rotate_value != 0) {
        if (clock.getElapsedTime().asMilliseconds() >= 1000 / 30) { // for 30 rot per seconds
            clock.restart();
            img->rotate(rotate_value);
        }
    }
}

void WidgetLoader::onFinishView()
{}

void WidgetLoader::set_img(const std::string &path)
{
    img->set_img(path);
}

void WidgetLoader::set_scale_bysize(sf::Vector2<float> size)
{
    transform.scale = size;
    img->set_scale_bysize(size);
}

void WidgetLoader::set_background(sf::Color color)
{
    background_color = color;
}

void WidgetLoader::set_rotation(float angle)
{
    rotate_value = angle;
}

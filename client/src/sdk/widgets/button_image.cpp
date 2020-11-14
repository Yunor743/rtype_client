/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/button_image.hpp"

WidgetButtonImage::WidgetButtonImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    WidgetButtonText(view_intent, parent_trans, main_window, theme)
{
    size = {50, 50};
    scale(size);
}

void WidgetButtonImage::onUpdateView()
{
    if (is_hover() && is_active) {
        if (pointer_curs) {
            window.setMouseCursor(pointer_curs.value());
            arrow_curs.unlock();
            pointer_curs.lock();
        }
        background_color = hover_color;
    } else {
        if (arrow_curs) {
            window.setMouseCursor(arrow_curs.value());
            pointer_curs.unlock();
            arrow_curs.lock();
        }
        background_color = base_color;
    }
    if (is_hover() && Input::getKeys(keyboard::LeftClick) == keyboard::KeyStatus::PRESSED) {
        background_color = click_color;
        is_clicked = true;
    } else if (is_clicked  && is_hover() && Input::getKeys(keyboard::LeftClick) == keyboard::KeyStatus::RELEASED) {
        click();
        is_clicked = false;
    } else {
        is_clicked = false;
    }
    if (!is_active) {
        background_color = deactivate_color;
    }
    background.setFillColor(background_color);
    window.draw(sprite);
    window.draw(border);
}

void WidgetButtonImage::set_image(const std::string &path)
{
    text.loadFromFile(path);
    sprite.setTexture(text);
    size.x = static_cast<float>(text.getSize().x);
    size.y = static_cast<float>(text.getSize().y);
    scale(size);
}

void WidgetButtonImage::set_size(sf::Vector2<float> newsize)
{
    sprite.setScale({newsize.x / size.x, newsize.y / size.y});
    size = newsize;
    transform.scale = size;
    border.setSize({transform.scale.x - (padding_border * 2), transform.scale.y - (padding_border * 2)});
    scale(size);
}

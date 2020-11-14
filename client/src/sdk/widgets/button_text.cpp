/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/button_text.hpp"

WidgetButtonText::WidgetButtonText(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
    transform.position = {0, 0};
    add_widget<WidgetText>("btn text", reinterpret_cast<Itheme<Icolors *> *>(theme));
    text = get_fragment<WidgetText>("btn text");
    text->move({(transform.scale.y / 2) - (text->get_size().y / 2), 3});
    set_color(theme->getPrimary().value());
    set_background_color(theme->getTertiary().value());
    set_hover_color(theme->getSecondary().value());
    set_click_color(theme->getPrimary().value());
    border.setPosition({padding_border, padding_border});
    border.setFillColor(theme->getColor("Transparent").value());
    border.setOutlineThickness(padding_border);
    border.setOutlineColor(theme->getColor("Black").value());
    arrow_curs->loadFromSystem(sf::Cursor::Arrow);
    pointer_curs->loadFromSystem(sf::Cursor::Hand);
    arrow_curs.unlock();
    pointer_curs.unlock();
    reload();
}

void WidgetButtonText::reload()
{
    auto text_size = text->get_size();
    transform.scale = {
        text_size.x + (padding_width * 2),
        text_size.y + (padding_height * 2)
    };
    text->scale(transform.scale);
    text->move({padding_width, (transform.scale.y / 2) - (text_size.y / 2)});
    border.setSize({transform.scale.x - (padding_border * 2), transform.scale.y - (padding_border * 2)});
}

bool WidgetButtonText::is_hover()
{
    auto pos = transform.position;
    pos.x += parent_transform.position.x;
    pos.y += parent_transform.position.y;
    auto mouse = Input::getMouse();
    if (mouse.x < pos.x || mouse.x > pos.x + transform.scale.x)
        return false;
    if (mouse.y < pos.y || mouse.y > pos.y + transform.scale.y)
        return false;
    return true;
}

void WidgetButtonText::onCreateView()
{}

void WidgetButtonText::onUpdateView()
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
    window.draw(border);
}

void WidgetButtonText::onFinishView()
{}

void WidgetButtonText::set_handler(std::function<void(void)> functor)
{
    handler = functor;
}

void WidgetButtonText::activate()
{
    is_active = true;
}

void WidgetButtonText::deactivate()
{
    is_active = false;
}

void WidgetButtonText::set_text(const std::string &newtext)
{
    text->set_text(newtext);
    reload();
}

void WidgetButtonText::set_font(const std::string &path)
{
    text->set_font(path);
}

void WidgetButtonText::set_fontsize(unsigned int newsize)
{
    text->set_fontsize(newsize);
}

void WidgetButtonText::set_color(sf::Color color)
{
    text->set_color(color);
}

void WidgetButtonText::set_background_color(sf::Color color)
{
    base_color = color;
}

void WidgetButtonText::set_hover_color(sf::Color color)
{
    hover_color = color;
}

void WidgetButtonText::set_click_color(sf::Color color)
{
    click_color = color;
}

void WidgetButtonText::set_deactivate_color(sf::Color color)
{
    deactivate_color = color;
}

void WidgetButtonText::click()
{
    if (is_active) {
        handler();
    }
}

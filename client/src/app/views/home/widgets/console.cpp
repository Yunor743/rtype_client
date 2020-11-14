/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/home/widgets/console.hpp"
#include "app/views/home/fragments/bottombar.hpp"
#include "app/res/theme.hpp"
#include "app/res/string.hpp"

void Console::updateStack() {
    sf::Vector2<float> pos = {5, 0};
    if (is_fold) {
        stack[max_stack_limit - 1]->move({5, 0});
    } else {
        for (auto i = 0; i < max_stack_limit; ++i) {
            stack[i]->move(pos);
            pos.y += log_character_height;
        }
    }
}

void Console::initStack() {
    auto theme = std::make_unique<Theme>();
    auto theme_ptr = reinterpret_cast<Itheme<Icolors *> *>(theme.get());

    std::string font_path = STRING("helvetica_font");
    for (auto i = 0; i < max_stack_limit; ++i) {
        add_widget<WidgetText>("log_" + std::to_string(i), theme_ptr);
        stack[i] = get_fragment<WidgetText>("log_" + std::to_string(i));
        stack[i]->set_font(font_path);
        stack[i]->set_fontsize(15);
        stack[i]->set_color(sf::Color::Red);
        stack[i]->set_text("");
    }
    updateStack();
}

Console::Console(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
    auto color = theme->getColor("Black").value();
    color.a /= 2;
    background_color = color;
    border.setOutlineColor(theme->getColor("Black").value());
    border.setFillColor(theme->getColor("Transparent").value());
    border.setOutlineThickness(border_thickness);
    set_fold_pos({window::WIDTH / 2 + padding_left, window::HEIGHT - BottomBar::bar_height + margin_height});
    set_unfold_pos({fold_pos.x, fold_pos.y - unfold_size.y + fold_size.y });
    move(unfold_pos);
    scale(unfold_size);
    initStack();
    reload();
}

void Console::onCreateView()
{
    flip();
}

void Console::onUpdateView()
{
    window.draw(border);
}

void Console::onFinishView()
{}

void Console::set_fold_pos(sf::Vector2<float> newpos)
{
    fold_pos = newpos;
}

void Console::set_fold_size(sf::Vector2<float> newsize)
{
    fold_size = newsize;
}

void Console::set_unfold_pos(sf::Vector2<float> newpos)
{
    unfold_pos = newpos;
}

void Console::set_unfold_size(sf::Vector2<float> newsize)
{
    unfold_size = newsize;
}

void Console::reload()
{
    if (is_fold) {
        move(fold_pos);
        scale(fold_size);
        for (auto i = 0; i < max_stack_limit - 1; ++i) {
            stack[i]->hide();
        }
    } else {
        move(unfold_pos);
        scale(unfold_size);
        for (auto i = 0; i < max_stack_limit - 1; ++i) {
            stack[i]->unhide();
        }
    }
    border.setPosition({border_thickness, border_thickness});
    border.setSize({transform.scale.x - border_thickness * 2, transform.scale.y - border_thickness * 2});

}


void Console::fold()
{
    is_fold = true;
    reload();
}

void Console::unfold()
{
    is_fold = false;
    reload();
}

void Console::flip()
{
    if (is_fold) {
        unfold();
    } else {
        fold();
    }
    updateStack();
}

void Console::log(const std::string &message)
{
    for (auto i = 1; i < max_stack_limit; ++i)
        stack[i - 1]->set_text(stack[i]->get_text());
    stack[max_stack_limit - 1]->set_text(message);
    std::cout << message << std::endl;
}

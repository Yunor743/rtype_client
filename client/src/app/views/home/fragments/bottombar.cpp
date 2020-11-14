/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/theme.hpp"
#include "app/window.hpp"
#include "app/views/home/fragments/bottombar.hpp"
#include "app/res/string.hpp"

BottomBar::BottomBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, window::HEIGHT - bar_height};
    transform.scale = {window::WIDTH, bar_height};
    background_color = Theme().getSecondary().value();
    add_widget<WidgetButtonImage>("Extend button", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    extend_btn = get_fragment<WidgetButtonImage>("Extend button");
    extend_btn->set_hover_color(Theme().getColor("buttons hover").value());
    extend_btn->set_click_color(Theme().getColor("buttons click").value());
    extend_btn->set_deactivate_color(Theme().getColor("buttons deactivate").value());
    extend_btn->set_image(STRING("extend image"));
    extend_btn->activate();
    extend_btn->set_handler([&](){
        console->flip();
    });
    extend_btn->move({window::WIDTH / 2 + 750, 3});
    extend_btn->set_size({25, 25});
}

void BottomBar::onCreateView()
{}

void BottomBar::onUpdateView()
{}

void BottomBar::onFinishView()
{}

void BottomBar::set_console(Console *newconsole)
{
    console = newconsole;
}


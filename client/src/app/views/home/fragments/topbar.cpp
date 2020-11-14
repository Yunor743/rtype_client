/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/res/theme.hpp"
#include "app/res/string.hpp"
#include "app/window.hpp"
#include "app/views/home/fragments/topbar.hpp"

TopBar::TopBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, 0};
    transform.scale = {window::WIDTH, bar_height};
    background_color = Theme().getSecondary().value();
    // add fps text
    add_widget<WidgetText>("text fps", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    text = get_fragment<WidgetText>("text fps");
    text->set_font(STRING("helvetica_font"));
    text->set_fontsize(15);
    text->set_color(sf::Color::Yellow);
    text->move({window::WIDTH - 50, 12});

    // add disconnect button
    add_widget<WidgetButtonText>("disconnect btn", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    disconnect = get_fragment<WidgetButtonText>("disconnect btn");
//    disconnect->scale()
    disconnect->move({window::WIDTH / 2 - 300, 10});
//    disconnect->scale({90, 30});
    disconnect->set_hover_color(Theme().getColor("buttons hover").value());
    disconnect->set_click_color(Theme().getColor("buttons click").value());
    disconnect->set_deactivate_color(Theme().getColor("buttons deactivate").value());
    disconnect->set_font(STRING("helvetica_font"));
    disconnect->set_fontsize(15);
    disconnect->set_text(STRING("disconnect"));
    disconnect->deactivate();
    disconnect->set_handler([&](){
        game->disconnect();
    });

    // add connect button
    add_widget<WidgetButtonText>("connect btn", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    connect = get_fragment<WidgetButtonText>("connect btn");
    connect->move({window::WIDTH / 2 + 210, 10});
    connect->set_hover_color(Theme().getColor("buttons hover").value());
    connect->set_click_color(Theme().getColor("buttons click").value());
    connect->set_deactivate_color(Theme().getColor("buttons deactivate").value());
    connect->set_font(STRING("helvetica_font"));
    connect->set_fontsize(15);
    connect->set_text(STRING("connect"));
    connect->activate();
    connect->set_handler([&](){
        ip_entry->submit();
    });

    // add text_entry for ip
    add_widget<WidgetText_entry>("IP entry", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    ip_entry = get_fragment<WidgetText_entry>("IP entry");
    ip_entry->move({window::WIDTH / 2 - 200, 12});
    ip_entry->scale({400, 25});
    ip_entry->set_font(STRING("helvetica_font"));
    ip_entry->set_fontsize(17);
    ip_entry->set_color(Theme().getPrimary().value());
    ip_entry->set_background(Theme().getTertiary().value());
    ip_entry->set_placeholder(STRING("IP_entry placeholder"));
    ip_entry->set_placeholder_color(Theme().getColor("Light Gray").value());
    ip_entry->set_maxchar_limit(40);
    ip_entry->set_handler([&](std::string_view str){
        game->connect(std::string(str));
    });
    // bottom line
    bottom_border.setPosition({0, bar_height - 5});
    bottom_border.setSize({window::WIDTH, 5});
    bottom_border.setFillColor(sf::Color::Black);
    bottom_border.setOutlineColor(sf::Color::Black);
    clock.restart();
}

void TopBar::onCreateView()
{
//    ip_entry->setText("10.62.105.147:25555");   // TODO temp code for debug
    ip_entry->setText("127.0.0.1:25555");   // TODO temp code for debug
}

void TopBar::onUpdateView()
{
    if (is_connect) {
        if (*is_connect) {
            disconnect->activate();
        } else {
            disconnect->deactivate();
        }
    }
    fps++;
    if (clock.getElapsedTime().asSeconds() >= 1) {
        text->set_text("fps:" + std::to_string(fps));
        fps = 0;
        clock.restart();
    }
    window.draw(bottom_border);
}

void TopBar::onFinishView()
{}

void TopBar::set_is_connect(bool *ptr)
{
    is_connect = ptr;
}

void TopBar::set_game(Game *newgame)
{
    game = newgame;
}

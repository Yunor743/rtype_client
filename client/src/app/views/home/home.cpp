/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/image.hpp"
#include "app/res/string.hpp"
#include "app/res/theme.hpp"
#include "app/window.hpp"
#include "app/views/home/home.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window, {window::WIDTH, window::HEIGHT})
{
    add_fragment<TopBar>("Topbar");
    top_bar = get_fragment<TopBar>("Topbar");
    top_bar->z_index = 5;
    add_fragment<Game>("GameScreen");
    game = get_fragment<Game>("GameScreen");
    game->z_index = 2;
    add_fragment<BottomBar>("BottomBar");
    bottom_bar = get_fragment<BottomBar>("BottomBar");
    bottom_bar->z_index = 5;
    add_widget<Console>("console", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    console = get_fragment<Console>("console");
    console->z_index = 7;
    // make connection between fragments
    top_bar->set_game(game);
    game->set_console(console);
    bottom_bar->set_console(console);
    // Adding foxy
    add_widget<WidgetImage>("foxy", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    auto foxy = get_fragment<WidgetImage>("foxy");
    foxy->set_img(STRING("foxy_head_trans_gray"));
    foxy->set_scale_bysize({200, 200});
    foxy->move({window::WIDTH / 2 - 100, window::HEIGHT / 2 - 150});
    foxy->z_index = 0;
}

void HomeView::onCreateView()
{
    top_bar->set_is_connect(game->get_is_connect());
    console->log("Loading done ! Welcome on rtype client");
}

void HomeView::onUpdateView()
{}

void HomeView::onFinishView()
{}

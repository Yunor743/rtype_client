/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <memory>
#include "sdk/widgets/image.hpp"
#include "sdk/widgets/loader.hpp"
#include "app/res/string.hpp"
#include "app/res/theme.hpp"
#include "app/window.hpp"
#include "app/views/loading/loading.hpp"

LoadingView::LoadingView(sf::RenderWindow &window) : Iview(window, {window::WIDTH, window::HEIGHT})
{
    auto theme = std::make_unique<Theme>();
    // Adding foxy
    add_widget<WidgetImage>("Image", reinterpret_cast<Itheme<Icolors *> *>(theme.get()));
    auto foxy = get_fragment<WidgetImage>("Image");
    foxy->set_img(STRING("foxy_head_trans_coffe"));
    foxy->set_scale_bysize({200, 200});
    foxy->move({window::WIDTH / 2 - 100, window::HEIGHT / 2 - 150});
    foxy->z_index = 0;

    // Adding Loaders:
    // green
    add_widget<WidgetLoader>("GreenLoader", reinterpret_cast<Itheme<Icolors *> *>(theme.get()));
    auto loader = get_fragment<WidgetLoader>("GreenLoader");
    loader->set_img(STRING("Loader_Green"));
    loader->set_scale_bysize({350, 350});
    loader->move({window::WIDTH / 2 - 175, window::HEIGHT / 2 - 215});
    loader->set_rotation(5);
    loader->z_index = 1;
    // blue
    add_widget<WidgetLoader>("BlueLoader", reinterpret_cast<Itheme<Icolors *> *>(theme.get()));
    loader = get_fragment<WidgetLoader>("BlueLoader");
    loader->set_img(STRING("Loader_Blue"));
    loader->set_scale_bysize({400, 400});
    loader->move({window::WIDTH / 2 - 200, window::HEIGHT / 2 - 240});
    loader->set_rotation(-5);
    loader->z_index = 2;
    clock.restart();
}

void LoadingView::onCreateView()
{}

void LoadingView::onUpdateView()
{
    if (clock.getElapsedTime().asSeconds() >= loading_time) {
        set_intent("home");
    }
}

void LoadingView::onFinishView()
{}

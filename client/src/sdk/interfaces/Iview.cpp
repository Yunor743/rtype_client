/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <algorithm>
#include "sdk/interfaces/Iview.hpp"
#include "app/window.hpp"


Iview::Iview(sf::RenderWindow &main_window, sf::Vector2<float> size) :
    absolute({size, {0, 0}}), window(main_window), Ifragment(intent, absolute, main_window)
{
    transform = absolute;
}

std::optional<std::string> Iview::get_intent()
{
    auto ret = intent;
    intent.reset();
    return ret;
}

void Iview::runCreate()
{
    // sort by z_index
    std::sort(fragments.begin(), fragments.end(), [](const auto &left, const auto &right) {
        return left.second->z_index < right.second->z_index;
    });
    for (auto &fragment : fragments) {
        fragment.second->runCreate();
    }
    onCreateView();
}

void Iview::runUpdate()
{
    onUpdateView();
    for (auto &fragment : fragments) {
        fragment.second->runUpdate();
    }
    // the fragments edit the window view so after, i need to reset it to default
    window.setView(window.getDefaultView());
}

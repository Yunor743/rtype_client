/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_HOME_HPP_
#define _APP_VIEWS_HOME_HPP_

#include "sdk/interfaces/Iview.hpp"
#include "app/views/home/fragments/topbar.hpp"
#include "app/views/home/fragments/bottombar.hpp"
#include "app/views/home/fragments/game.hpp"
#include "app/views/home/widgets/console.hpp"

class HomeView : public Iview {
    TopBar *top_bar = nullptr;
    Game *game = nullptr;
    BottomBar *bottom_bar = nullptr;
    Console *console = nullptr;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    explicit HomeView(sf::RenderWindow &window);
};

#endif
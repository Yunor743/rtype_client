/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_LOADING_HPP_
#define _APP_VIEWS_LOADING_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iview.hpp"

class LoadingView : public Iview {
    static constexpr auto loading_time = 1; // TODO change to 3
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    sf::Clock clock;
public:
    explicit LoadingView(sf::RenderWindow &window);
};

#endif
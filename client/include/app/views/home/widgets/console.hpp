/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_HOME_WIDGETS_CONSOLE_HPP_
#define _APP_VIEWS_HOME_WIDGETS_CONSOLE_HPP_

#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/widgets/text.hpp"
#include "app/window.hpp"

class Console : public Iwidget {
    bool is_fold = false;
    static constexpr auto margin_height = 3;
    static constexpr auto padding_left = -750;
    static constexpr auto border_thickness = 3;
    static constexpr auto max_stack_limit = 44;
    static constexpr auto log_character_height = 18;
    sf::Vector2<float> fold_pos = {0, 0};
    sf::Vector2<float> unfold_pos = {0, 0};
    sf::Vector2<float> fold_size = {1500, 25};
    sf::Vector2<float> unfold_size = {1500, 800};
    std::array<WidgetText *, max_stack_limit> stack;
    sf::RectangleShape border;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    void initStack();
    void updateStack();
public:
    Console(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_fold_pos(sf::Vector2<float> newpos);
    void set_fold_size(sf::Vector2<float> newsize);
    void set_unfold_pos(sf::Vector2<float> newpos);
    void set_unfold_size(sf::Vector2<float> newsize);
    void reload();
    void fold();
    void unfold();
    void flip();
    void log(const std::string &message);
};

#endif
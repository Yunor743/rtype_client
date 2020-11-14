/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_FRAGMENTS_BOTTOMBAR_HPP_
#define _APP_VIEWS_FRAGMENTS_BOTTOMBAR_HPP_

#include "sdk/interfaces/Ifragment.hpp"
#include "sdk/widgets/button_image.hpp"
#include "app/views/home/widgets/console.hpp"

class BottomBar : public Ifragment {
    Console *console = nullptr;
    WidgetButtonImage *extend_btn;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    static constexpr auto bar_height = 30;
    BottomBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window);
    void set_console(Console *newconsole);
};

#endif
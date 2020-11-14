/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_TEXT_HPP_
#define _SDK_WIDGETS_TEXT_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"

class WidgetText : public Iwidget {
    static constexpr auto text_padding_height = 3;
    static constexpr auto text_padding_width = 2;
    bool is_hide = false;
    sf::Vector2<float> size;
    sf::Font font;
    sf::Text text;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    void reload();
public:
    WidgetText(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_font(const std::string &path);
    void set_fontsize(unsigned int newsize);
    void set_color(sf::Color color);
    void set_text(const std::string &newtext);
    void set_background(sf::Color color);
    [[nodiscard]] sf::Vector2<float> get_size() const;
    [[nodiscard]] std::string get_text() const;
    void hide();
    void unhide();
};

#endif
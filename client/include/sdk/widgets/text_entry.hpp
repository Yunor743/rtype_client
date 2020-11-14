/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_TEXT_ENTRY_HPP_
#define _SDK_WIDGETS_TEXT_ENTRY_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"
#include "sdk/widgets/text.hpp"
#include "sdk/managers/inputs.hpp"
#include "sdk/utils/varlock.hpp"

class WidgetText_entry : public Iwidget {
    static constexpr auto cursor_timeout = 750;
    static constexpr auto delete_timeout = 750;
    sdkutils::VarLock<sf::Cursor> arrow_curs;
    sdkutils::VarLock<sf::Cursor> text_curs;
    bool isfocus = false;
    bool is_placeholdermode = true;
    sdkutils::VarLock<sf::Clock> delete_clock;
    sf::Clock cursor_clock;
    sdkutils::VarLock<sf::RectangleShape> cursor;
    sf::Vector2<float> size;
    WidgetText *text = nullptr;
    sf::Color textcolor;
    std::string data = "";
    std::string placeholder = "";
    sf::Color placeholder_color = sf::Color::White;
    std::function<void(std::string_view)> handler;
    unsigned short maxchar_limit = 20;
    bool is_hover();
    bool is_clicked();
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    void reload();
public:
    WidgetText_entry(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void clear();
    void set_font(const std::string &path);
    void set_fontsize(unsigned int newsize);
    void set_color(sf::Color color);
    void set_background(sf::Color color);
    void set_handler(std::function<void(std::string_view)> functor);
    void set_placeholder(const std::string &str);
    void set_placeholder_color(sf::Color color);
    void set_maxchar_limit(unsigned short newlimit);
    void submit();
    void setText(const std::string &new_text);
};

#endif
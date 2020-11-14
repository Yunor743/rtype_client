/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/text_entry.hpp"

WidgetText_entry::WidgetText_entry(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
    add_widget<WidgetText>("text", theme);
    text = get_fragment<WidgetText>("text");
    scale({100, 12});
    arrow_curs->loadFromSystem(sf::Cursor::Arrow);
    text_curs->loadFromSystem(sf::Cursor::Text);
    arrow_curs.unlock();
    text_curs.unlock();
    cursor->setSize({2, 20});
    cursor.unlock();
    cursor->setFillColor(sf::Color::Black);
    cursor_clock.restart();
    delete_clock.lock();
    reload();
}

bool WidgetText_entry::is_hover()
{
    auto mouse = Input::getMouse();
    if (mouse.x < transform.position.x || mouse.x > transform.position.x + transform.scale.x)
        return false;
    if (mouse.y < transform.position.y || mouse.y > transform.position.y + transform.scale.y)
        return false;
    return true;
}

bool WidgetText_entry::is_clicked()
{
    return is_hover() && Input::getKeys(keyboard::LeftClick) == keyboard::KeyStatus::PRESSED;
}

void WidgetText_entry::onCreateView()
{}

void WidgetText_entry::onUpdateView()
{
    if (is_hover()) {
        if (text_curs) {
            window.setMouseCursor(text_curs.value());
            arrow_curs.unlock();
            text_curs.lock();
        }
    } else {
        if (arrow_curs) {
            window.setMouseCursor(arrow_curs.value());
            text_curs.unlock();
            arrow_curs.lock();
        }
    }

    if (is_clicked())
        isfocus = true;
    else if (!is_hover() && Input::getKeys(keyboard::LeftClick) == keyboard::KeyStatus::PRESSED)
        isfocus = false;
    if (isfocus) {
        bool has_enter_or_delete = false;
        auto key_queue = Input::getKeysQueue();

        if (delete_clock) {
            // check if delete is always pressed or quit
            if (Input::getKeys(keyboard::Key::BackSpace) != keyboard::KeyStatus::PRESSED) {
                delete_clock.lock();
            } else if (delete_clock->getElapsedTime().asMilliseconds() >= delete_timeout) {
                delete_clock.unlock();
                if (!data.empty())
                    data.pop_back();
            } else {
                delete_clock.unlock();
            }
            has_enter_or_delete = true;
        } else {
            for (auto i = 0; i < key_queue.size; ++i) {
                if (key_queue.data[i].pressed) {
                    // delete
                    if (key_queue.data[i].key == keyboard::Key::BackSpace) {
                        has_enter_or_delete = true;
                        if (!data.empty())
                            data.pop_back();
                        delete_clock.unlock()->restart();
                        delete_clock.unlock();
                        continue;
                    } else {
                        delete_clock.lock();
                    }
                    // enter
                    if (key_queue.data[i].key == keyboard::Key::Enter) {
                        has_enter_or_delete = true;
                        submit();
                        continue;
                    }
                }
            }
        }
        if (has_enter_or_delete) {
            reload();
        } else {
            if (data.size() < maxchar_limit) {
                auto text_entered = Input::get_text_entered();
                if (!text_entered.empty()) {
                    data += text_entered;
                    reload();
                }
            }
        }
    }
    if (isfocus) {
        if (cursor_clock.getElapsedTime().asMilliseconds() >= cursor_timeout) {
            cursor_clock.restart();
            if (cursor) {
                cursor.lock();
            } else {
                cursor.unlock();
            }
        }
        if (cursor) window.draw(cursor.value());
    }
    if (!data.empty())
        text->set_text(data);
    if (data.empty() && !is_placeholdermode) {
        is_placeholdermode = true;
        reload();
    }
    if (!data.empty() && is_placeholdermode) {
        is_placeholdermode = false;
        reload();
    }
}

void WidgetText_entry::onFinishView()
{}

void WidgetText_entry::reload()
{
    if (is_placeholdermode) {
        text->set_text(placeholder);
        text->set_color(placeholder_color);
    } else {
        text->set_color(textcolor);
        text->set_text(data);
    }
    if (data.empty()) {
        cursor.unlock()->setPosition(2, 2);
    } else
        cursor.unlock()->setPosition(text->get_size().x, 2);
}

void WidgetText_entry::clear()
{
    data.clear();
    reload();
}

void WidgetText_entry::set_font(const std::string &path)
{
    text->set_font(path);
}

void WidgetText_entry::set_fontsize(unsigned int newsize)
{
    text->set_fontsize(newsize);
}

void WidgetText_entry::set_color(sf::Color color)
{
    textcolor = color;
    text->set_color(textcolor);
}

void WidgetText_entry::set_background(sf::Color color)
{
    background_color = color;
}

void WidgetText_entry::set_handler(std::function<void(std::string_view)> functor)
{
    handler = functor;
}

void WidgetText_entry::set_placeholder(const std::string &str)
{
    placeholder = str;
    reload();
}

void WidgetText_entry::set_placeholder_color(sf::Color color)
{
    placeholder_color = color;
    reload();
}

void WidgetText_entry::set_maxchar_limit(unsigned short newlimit)
{
    maxchar_limit = newlimit;
}

void WidgetText_entry::submit()
{
    handler(data);
    clear();
}

void WidgetText_entry::setText(const std::string &new_text)
{
    data = new_text;
    reload();
}





/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/managers/inputs.hpp"

void Input::init(Event *ev)
{
    event = ev;
}

sf::Vector2<int> Input::getMouse()
{
    return event->mouse;
}

keyboard::KeyStatus Input::getKeys(keyboard::Key key)
{
    return event->keys_state.at(key);
}

Event::KeysEvent Input::getKeysQueue()
{
    return event->keys_event;
}

std::string Input::get_text_entered()
{
    return event->text_entered;
}

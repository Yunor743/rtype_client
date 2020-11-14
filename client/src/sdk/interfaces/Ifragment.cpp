/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/window.hpp"
#include "sdk/interfaces/Ifragment.hpp"

void Ifragment::set_intent(const std::string &view)
{
    intent_ref.emplace(view);
}

Ifragment *Ifragment::get_fragment(const std::string &key)
{
    auto item = std::find_if(fragments.begin(), fragments.end(), [&](const auto &pair){
        return pair.first == key;
    });
    if (item == fragments.end())
        return nullptr;
    return item->second;
}

Ifragment::Ifragment(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window) :
        intent_ref(view_intent), parent_transform(parent_trans), window(main_window)
{}

Ifragment::~Ifragment()
{
    for (auto &fragment : fragments) {
        delete fragment.second;
    }
}

void Ifragment::runCreate()
{
    compute_content();
    const auto parent_view = window.getView();
    window.setView(content);
    // background
    background.setFillColor(background_color);
    background.setSize(transform.scale);
    background.setPosition(0, 0);
    // sort by z_index
    std::sort(fragments.begin(), fragments.end(), [](const auto &left, const auto &right) {
        return left.second->z_index < right.second->z_index;
    });
    for (auto &fragment : fragments) {
        fragment.second->runCreate();
    }
    onCreateView();
    window.setView(parent_view);
}

void Ifragment::runUpdate()
{
    auto parent_view = window.getView();
    window.setView(content);
    window.draw(background);
    for (auto &fragment : fragments) {
        fragment.second->runUpdate();
    }
    window.setView(content);
    onUpdateView();
//    window.setView(parent_view);
}

void Ifragment::runFinish()
{
    for (auto &fragment : fragments) {
        fragment.second->runFinish();
    }
    onFinishView();
}

void Ifragment::compute_content()
{
    float diff;
    if (transform.position.x < 0) {
        if (std::abs(transform.position.x) > transform.scale.x) {
            transform.scale.x = 0;
        } else {
            diff = std::abs(transform.position.x);
            transform.scale.x -= diff;
        }
    }
    if (transform.position.y < 0) {
        if (std::abs(transform.position.y) > transform.scale.y) {
            transform.scale.y = 0;
        } else {
            diff = std::abs(transform.position.y);
            transform.scale.y -= diff;
        }
    }
    sf::Vector2<float> parent_position_offset;
    parent_position_offset.x = parent_transform.position.x < 0 ? std::abs(parent_transform.position.x) : 0;
    parent_position_offset.y = parent_transform.position.y < 0 ? std::abs(parent_transform.position.y) : 0;
    if (transform.position.x + transform.scale.x - parent_position_offset.x > parent_transform.scale.x) {
        if (transform.position.x > parent_transform.scale.x) {
            transform.scale.x = 0;
        } else {
            diff = transform.position.x + transform.scale.x - parent_transform.scale.x - parent_position_offset.x;
            transform.scale.x -= diff;
        }
    }
    if (transform.position.y + transform.scale.y - parent_position_offset.x > parent_transform.scale.y) {
        if (transform.position.y > parent_transform.scale.y) {
            transform.scale.y = 0;
        } else {
            diff = transform.position.y + transform.scale.y - parent_transform.scale.y - parent_position_offset.y;
            transform.scale.y -= diff;
        }
    }
    sf::Vector2<float> center;
    center.x = transform.scale.x / 2;
    center.y = transform.scale.y / 2;
    transform.position.x += parent_transform.position.x < 0 ? parent_transform.position.x : 0;
    transform.position.y += parent_transform.position.y < 0 ? parent_transform.position.y : 0;
    const auto abs_posx = parent_transform.position.x + transform.position.x;
    const auto abs_posy = parent_transform.position.y + transform.position.y;
    const auto abs_posx_percent = abs_posx / window::WIDTH;
    const auto abs_posy_percent = abs_posy / window::HEIGHT;
    const auto abs_width_percent = transform.scale.x / window::WIDTH;
    const auto abs_height_percent = transform.scale.y / window::HEIGHT;
    // BUILD VIEW
    content.setCenter(center.x, center.y);
    content.setSize(transform.scale.x, transform.scale.y);
    content.setViewport(sf::FloatRect(abs_posx_percent, abs_posy_percent, abs_width_percent, abs_height_percent));
}

void Ifragment::move(sf::Vector2<float> pos)
{
    transform.position = pos;
    reload();
}

void Ifragment::scale(sf::Vector2<float> scale)
{
    transform.scale = scale;
    reload();
}

void Ifragment::setViewCenter(sf::Vector2<float> coords)
{
    content.setCenter(coords.x, coords.y);
}

[[nodiscard]] sf::Vector2<float> Ifragment::getViewCenter() const
{
    return content.getCenter();
}

void Ifragment::reload()
{
    background.setSize(transform.scale);
    compute_content();
}





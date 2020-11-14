/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/interfaces/Istring.hpp"

std::optional<std::string_view> Istring::get(const std::string &key)
{
    auto item = list.find(key);
    if (item == list.end())
        return std::nullopt;
    return std::optional<std::string_view>(item->second);
}

Istring &Istring::operator+=(const Istring &rhs) {
    for (const auto &item : rhs.list)
        this->list.emplace(item.first, item.second);
    return *this;
}

/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_ISTRING_HPP_
#define _SDK_INTERFACES_ISTRING_HPP_

#include <map>
#include <string>
#include <optional>
#include <string_view>

class Istring {
protected:
    std::map<std::string, const std::string> list;
public:
    [[nodiscard]] std::optional<std::string_view> get(const std::string &key);
    Istring &operator+=(const Istring &rhs);
};

#endif
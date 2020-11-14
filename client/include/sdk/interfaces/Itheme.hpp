/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_ITHEME_HPP_
#define _SDK_INTERFACES_ITHEME_HPP_

#include <map>
#include <memory>
#include <sdk/interfaces/Icolors.hpp>

template<typename T>
class Itheme {
    std::unique_ptr<Icolors> colors;
    const std::string primary;
    const std::string secondary;
    const std::string tertiary;
public:
    Itheme(const std::string &primary_key, const std::string &secondary_key, const std::string &tertiary_key) :
            primary(primary_key), secondary(secondary_key), tertiary(tertiary_key)
    {
        static_assert(std::is_base_of<Icolors, T>::value, "T doesn't derive from Icolors");
        colors = std::make_unique<T>();
    }

    [[nodiscard]] std::optional<sf::Color> getPrimary() const;
    [[nodiscard]] std::optional<sf::Color> getSecondary() const;
    [[nodiscard]] std::optional<sf::Color> getTertiary() const;
    [[nodiscard]] std::optional<sf::Color> getColor(const std::string &key) const;
};

// Methods Definitions

template<typename T>
std::optional<sf::Color> Itheme<T>::getPrimary() const {
    return getColor(primary);
}

template<typename T>
std::optional<sf::Color> Itheme<T>::getSecondary() const {
    return getColor(secondary);
}

template<typename T>
std::optional<sf::Color> Itheme<T>::getTertiary() const {
    return getColor(tertiary);
}

template<typename T>
std::optional<sf::Color> Itheme<T>::getColor(const std::string &key) const {
    if (colors != nullptr)
        return colors->get(key);
    return std::nullopt;
}

#endif
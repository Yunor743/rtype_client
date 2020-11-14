/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_RES_THEME_LIGHT_HPP_
#define _APP_RES_THEME_LIGHT_HPP_

#include "sdk/interfaces/Itheme.hpp"
#include "app/res/colors.hpp"

class LightTheme : public Itheme<Colors> {
public:
    LightTheme() : Itheme("Glace Vanille",
                          "Vomi d'Alexis",
                          "White") {};
};

#endif
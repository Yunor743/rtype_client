/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_RES_THEME_DARK_HPP_
#define _APP_RES_THEME_DARK_HPP_

#include "sdk/interfaces/Itheme.hpp"
#include "app/res/colors.hpp"

class DarkTheme : public Itheme<Colors> {
public:
    DarkTheme() : Itheme("Discord : Sombre, mais pas noir",
                         "Background du Babel trop classe de Hugo",
                         "Discord : Bleu-violet") {};
};

#endif
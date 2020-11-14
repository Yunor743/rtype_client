/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_RES_STRING_HPP_
#define _APP_RES_STRING_HPP_

#include "app/res/strings/en.hpp"
#include "app/res/strings/fr.hpp"

/**
 * Set default string
 */
using String = EnString;

#define STRING(key) (std::string(String().get(key).value()))

#endif
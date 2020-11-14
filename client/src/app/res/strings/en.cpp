/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/strings/common.hpp"
#include "app/res/strings/en.hpp"

EnString::EnString()
{
    *this += CommonString();
    list.emplace("IP_entry placeholder", "Enter the server address : IP:PORT");
    list.emplace("disconnect", "Disconnect");
    list.emplace("connect", "Connect");
}

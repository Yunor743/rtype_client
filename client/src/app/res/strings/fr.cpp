/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/strings/common.hpp"
#include "app/res/strings/fr.hpp"

FrString::FrString()
{
    *this += CommonString();
    list.emplace("IP_entry placeholder", "Entrer l'addresse du serveur : IP:PORT");
    list.emplace("disconnect", "Deconnexion");
    list.emplace("connect", "Connexion");
}

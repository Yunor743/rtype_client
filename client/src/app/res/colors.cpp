/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/colors.hpp"

Colors::Colors() : Icolors()
{
    list.emplace("Black", sf::Color::Black);
    list.emplace("White", sf::Color::White);
    list.emplace("Red", sf::Color::Red);
    list.emplace("Green", sf::Color::Green);
    list.emplace("Blue", sf::Color::Blue);
    list.emplace("Yellow", sf::Color::Yellow);
    list.emplace("Magenta", sf::Color::Magenta);
    list.emplace("Cyan", sf::Color::Cyan);
    list.emplace("Transparent", sf::Color::Transparent);
    list.emplace("Light Gray", sf::Color(170, 170, 170));
    list.emplace("Glace Vanille", sf::Color(240, 229, 182));
    list.emplace("Vomi d'Alexis", sf::Color(204, 198, 182));
    list.emplace("Background du Babel trop classe de Hugo", sf::Color(34, 40, 64));
    list.emplace("Discord : Bleu-violet", sf::Color(114, 137, 218));
    list.emplace("Discord : Gris-violet", sf::Color(153, 170, 181));
    list.emplace("Discord : Sombre, mais pas noir", sf::Color(44, 47, 51));
    list.emplace("Discord : Pas noir mais presque", sf::Color(35, 39, 42));
    list.emplace("buttons hover", sf::Color(123, 126, 150));
    list.emplace("buttons click", sf::Color(66, 66, 66));
    list.emplace("buttons deactivate", sf::Color(97, 97, 97));
}
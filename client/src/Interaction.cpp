/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Interaction.cpp
*/

#include "Game.hpp"

void client::Interaction::setInteraction(int inter)
{
    //exemple tu feras bien plus propre surement avec un tableau de poiteur sur fonction mais là j'ai la flemme
    if (inter > 0 && inter < 4)
        _movement = inter;
    else if (inter == 4)
        _shoot = 1;
    else if (inter == 5)
        _quit = 1;
}

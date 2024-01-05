/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "Server.hpp"

int server::Server::run()
{
    Game game;
    //std::thread gameThread = std::thread(&Game::run, &game);

    _network.run(&game);
    return 0;
}

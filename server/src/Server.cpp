/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "Server.hpp"

int server::Server::run()
{
    _gameThread = std::thread(&Game::run, &_game);
    _network.run();
    return 0;
}
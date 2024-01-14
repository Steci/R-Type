/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "Client.hpp"

int client::Client::run()
{
    Game game;

    std::thread gameThread = std::thread(&Game::run, &game);
    _network.run(&game, &gameThread);
    return 0;
}

int client::Client::validatePort(int port) {
    if (port <= 0 || port > 65535) {
        return 9001;
    }
    return port;
}

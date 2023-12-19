/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "Client.hpp"

int client::Client::run()
{
    if (_network.connect() == 0) {
        _network.run();
    } else {
        return 84;
    }
    return 0;
}

int client::Client::validatePort(int port) {
    if (port <= 0 || port > 65535) {
        return 8080;
    }
    return port;
}

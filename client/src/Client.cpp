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

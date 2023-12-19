/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "Client.hpp"

int client::Client::run()
{
    _network.run();
    return 0;
}

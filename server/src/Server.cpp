/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "Server.hpp"

int server::Server::run()
{
    _network.run();
    return 0;
}
/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "Network.hpp"

int server::Client::readClient()
{
    char buffer[1024] = {0};
    int valread = read(_fd, buffer, 1024);

    if (valread == 0) {
        std::cout << "Client disconnected" << std::endl;
        return -1;
    }
    std::cout << buffer << std::endl;
    return 0;
}
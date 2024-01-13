/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Network.cpp
*/

#include "../include/Network.hpp"

std::vector<char> AConnection::serializeConnection() {
    std::vector<char> data;
    data.insert(data.end(), reinterpret_cast<char*>(&_connect), reinterpret_cast<char*>(&_connect) + sizeof(_connect));
    data.insert(data.end(), reinterpret_cast<char*>(&_connected), reinterpret_cast<char*>(&_connected) + sizeof(_connected));
    data.insert(data.end(), reinterpret_cast<char*>(&_createGame), reinterpret_cast<char*>(&_createGame) + sizeof(_createGame));
    return data;
}

void AConnection::deserializeConnection(std::vector<char> data) {
    std::memcpy(&_connect, data.data(), sizeof(_connect));
    std::memcpy(&_connected, data.data() + sizeof(_connect), sizeof(_connected));
    std::memcpy(&_createGame, data.data() + sizeof(_connect) + sizeof(_connected), sizeof(_createGame));
}

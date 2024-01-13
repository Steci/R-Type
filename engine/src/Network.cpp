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
    data.insert(data.end(), reinterpret_cast<char*>(&_gameId), reinterpret_cast<char*>(&_gameId) + sizeof(_gameId));
    data.insert(data.end(), reinterpret_cast<char*>(&_gameIds), reinterpret_cast<char*>(&_gameIds) + sizeof(_gameIds));
    return data;
}

void AConnection::deserializeConnection(std::vector<char> data) {
    std::memcpy(&_connect, data.data(), sizeof(_connect));
    std::memcpy(&_connected, data.data() + sizeof(_connect), sizeof(_connected));
    std::memcpy(&_createGame, data.data() + sizeof(_connect) + sizeof(_connected), sizeof(_createGame));
    std::memcpy(&_gameId, data.data() + sizeof(_connect) + sizeof(_connected) + sizeof(_createGame), sizeof(_gameId));
    std::memcpy(&_gameIds, data.data() + sizeof(_connect) + sizeof(_connected) + sizeof(_createGame) + sizeof(_gameId), sizeof(_gameIds));
}

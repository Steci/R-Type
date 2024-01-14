/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Network.cpp
*/

#include "EngineNetwork.hpp"

std::vector<char> AConnection::serializeConnection() {
    std::vector<char> data;
    data.reserve(sizeof(_connected) + sizeof(_createGame) + sizeof(_JoinGame) + sizeof(_gameId) + _gameIds.size() * sizeof(int) + sizeof(int));
    data.insert(data.end(), reinterpret_cast<char*>(&_connected), reinterpret_cast<char*>(&_connected) + sizeof(_connected));
    data.insert(data.end(), reinterpret_cast<char*>(&_createGame), reinterpret_cast<char*>(&_createGame) + sizeof(_createGame));
    data.insert(data.end(), reinterpret_cast<char*>(&_JoinGame), reinterpret_cast<char*>(&_JoinGame) + sizeof(_JoinGame));
    data.insert(data.end(), reinterpret_cast<char*>(&_gameId), reinterpret_cast<char*>(&_gameId) + sizeof(_gameId));

    for (int id : _gameIds) {
        data.insert(data.end(), reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + sizeof(id));
    }
    int end = -1;
    data.insert(data.end(), reinterpret_cast<char*>(&end), reinterpret_cast<char*>(&end) + sizeof(end));
    return data;
}

void AConnection::deserializeConnection(std::vector<char> data) {
    size_t size = 0;  // Use the appropriate unsigned type
    std::memcpy(&_connected, data.data() + size, sizeof(_connected));
    size += sizeof(_connected);
    std::memcpy(&_createGame, data.data() + size, sizeof(_createGame));
    size += sizeof(_createGame);
    std::memcpy(&_JoinGame, data.data() + size, sizeof(_JoinGame));
    size += sizeof(_JoinGame);
    std::memcpy(&_gameId, data.data() + size, sizeof(_gameId));
    size += sizeof(_gameId);
    while (size < data.size() && data[size] != -1) {
        int gameId;
        if (size + sizeof(gameId) <= data.size()) {
            std::memcpy(&gameId, data.data() + size, sizeof(gameId));
            _gameIds.push_back(gameId);
            size += sizeof(gameId);
        }
    }
}

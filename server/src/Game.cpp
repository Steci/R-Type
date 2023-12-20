/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include <sstream>
#include <algorithm>
#include "Game.hpp"

server::Game::Game()
{
    _tick = 0;
}

server::Game::~Game()
{
}

std::pair<std::string, std::string> server::Game::parseCommand(const std::string& input) {
    std::istringstream iss(input);
    std::string command;
    std::string clientID;

    std::getline(iss, command, ' ');
    std::getline(iss, clientID, ' ');

    return {command, clientID};
}

bool findPlayerID(std::vector<std::pair<IEntity *, int>> playerList, int playerIndex)
{
    if (playerList.size() == 0)
        return false;
    for (auto pair : playerList) {
        if (pair.second == playerIndex)
            return true;
    }
    return false;
}

void server::Game::run()
{
    printf("Game started");
    SystemManager manager;
    std::vector<std::pair<IEntity *, int>> players;
    // printf("start loop");
    while (true) {
        _mutex.lock();
        if (_functions_server.size() > 0) {
            _functions = _functions_server;
            _functions_server.clear();
        }
        _mutex.unlock();

        for (auto& function : _functions) {
            // printf("Current function : %s\n", function.c_str());
            auto [command, clientID] = parseCommand(function);
            printf("\nCommand : %s\n", command.c_str());
            printf("\nClient ID : %s\n", clientID.c_str());
            if (command == "CONNECT") {
                printf("connection\n");
                if (players.size() >= 4)
                    continue;
                if (findPlayerID(players, atoi(clientID.c_str())))
                {
                    printf("player already connected");
                    continue;
                }
                // create entity
                IEntity *player = new E_Player();
                Engine::setTransformPos(*player, {50, (float)atoi(clientID.c_str()) * 100});
                // add entity to entities
                players.push_back({player, atoi(clientID.c_str())});
            }
            if (command == "DEBUG")
            {
                for (auto& player : players) {
                    printf("Player ID : %d\n", player.second);
                    printf("Player Position : %f, %f\n", Engine::getComponentRef<C_Transform>(*player.first)->_position.x, Engine::getComponentRef<C_Transform>(*player.first)->_position.y);
                }
            }
            if (command == "UP") {
                printf("up");
                // get the transform of the player with the clientID
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
                        // move the player
                        transform->_position.y -= 10;
                    }
                }
            }
            if (command == "DOWN") {
                printf("down");
                // get the transform of the player with the clientID
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
                        // move the player
                        transform->_position.y += 10;
                    }
                }
            }
            if (command == "LEFT") {
                printf("left");
                // get the transform of the player with the clientID
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
                        // move the player
                        transform->_position.x -= 10;
                    }
                }
            }
            if (command == "RIGHT") {
                printf("right");
                // get the transform of the player with the clientID
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
                        // move the player
                        transform->_position.x += 10;
                    }
                }
            }
            _mutex_client.lock();
            _functions_client.push_back("POS " + std::to_string(Engine::getComponentRef<C_Transform>(*players[0].first)->_position.x) + " " + std::to_string(Engine::getComponentRef<C_Transform>(*players[0].first)->_position.y) + " " + clientID);
            _mutex_client.unlock();
        }
        _functions.clear();
        manager.update();
        // printf("tick++");
        _tick++;
        // printf("tick = " << _tick);
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickSpeed));
    }
}

void server::Game::addFunction(std::string function)
{
    _mutex.lock();
    _functions_server.push_back(function);
    _mutex.unlock();
}

std::vector<std::string> server::Game::getFunctionsClient()
{
    _mutex_client.lock();
    std::vector<std::string> functions = _functions_client;
    _functions_client.clear();
    _mutex_client.unlock();
    return functions;
}
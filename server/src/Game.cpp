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
    manager.addSystem<S_Renderer>(800, 600, 60, "debug");
    std::vector<std::pair<IEntity *, int>> players;

    while (true) {
        _mutex.lock();
        if (_functions_server.size() > 0) {
            _functions = _functions_server;
            _functions_server.clear();
        }
        _mutex.unlock();

        for (auto& function : _functions) {
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
                manager.getSystem<S_Renderer>()->addEntity(player);
            }
            if (command == "QUIT") {
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        manager.getSystem<S_Renderer>()->removeEntity(player.first);
                        players.erase(std::remove(players.begin(), players.end(), player), players.end());
                        break;
                    }
                }
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
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
                        transform->_position.y -= 10;
                    }
                }
            }
            if (command == "DOWN") {
                printf("down");
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
                        transform->_position.y += 10;
                    }
                }
            }
            if (command == "LEFT") {
                printf("left");
                for (auto& player : players) {
                    if (player.second == atoi(clientID.c_str())) {
                        C_Transform *transform = Engine::getComponentRef<C_Transform>(*player.first);
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
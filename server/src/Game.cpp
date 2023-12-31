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
    _fonctions_map["QUIT"] = &server::Game::actionQuitCommand;
    _fonctions_map["DEBUG"] = &server::Game::actionDebugCommand;
    _fonctions_map["CONNECT"] = &server::Game::actionConnectCommand;
    _fonctions_map["UP"] = &server::Game::actionUpCommand;
    _fonctions_map["DOWN"] = &server::Game::actionDownCommand;
    _fonctions_map["LEFT"] = &server::Game::actionLeftCommand;
    _fonctions_map["RIGHT"] = &server::Game::actionRightCommand;
    _fonctions_map["SHOOT"] = &server::Game::actionShootCommand;
}

server::Game::~Game()
{
}

void server::Game::actionUpCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("up");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            transform->_position.y -= 10;
            if (transform->_animation == 3) {
                transform->_animation = 4;
            } else if (transform->_animation == 2) {
                transform->_animation = 1;
            } else if (transform->_animation == 1) {
                transform->_animation = 0;
            } else if (transform->_animation == 0) {
                transform->_animation = 3;
            } else {
                transform->_animation = 4;
            }
        }
    }
}

void server::Game::actionDownCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("down");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            transform->_position.y += 10;
            if (transform->_animation == 1) {
                transform->_animation = 2;
            } else if (transform->_animation == 4) {
                transform->_animation = 3;
            } else if (transform->_animation == 3) {
                transform->_animation = 0;
            } else if (transform->_animation == 0) {
                transform->_animation = 1;
            } else {
                transform->_animation = 2;
            }
        }
    }
}

void server::Game::actionLeftCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("left");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            transform->_position.x -= 10;
            if (transform->_animation == 2) {
                transform->_animation = 1;
            } else if (transform->_animation == 4) {
                transform->_animation = 3;
            } else {
                transform->_animation = 0;
            }
        }
    }
}

void server::Game::actionRightCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("right");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            transform->_position.x += 10;
            if (transform->_animation == 2) {
                transform->_animation = 1;
            } else if (transform->_animation == 4) {
                transform->_animation = 3;
            } else {
                transform->_animation = 0;
            }
        }
    }
}

void server::Game::actionDebugCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("debug\n");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        printf("Player ID : %d\n", clientID);
        printf("Player Position : %f, %f\n", Engine::getComponentRef<C_Transform>(playerEntity)->_position.x, Engine::getComponentRef<C_Transform>(playerEntity)->_position.y);
    }
}

void server::Game::actionQuitCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("quit\n");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        manager.getSystem<S_Renderer>()->removeEntity(&playerEntity);
        entities.remove(clientID);
    }
}

void server::Game::actionConnectCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("connection\n");
    int nbrPlayer = 0;
    const auto& sparseIds = entities.getAllIndices();
    for (auto id : sparseIds) {
        if (id != -1) {
            auto& tmpEntity = entities.get(id);
            if (typeid(tmpEntity) == typeid(E_Player)) {
                nbrPlayer++;
            }
        }
    }
    if (nbrPlayer >= 4)
        return;
    if (entities.exists(clientID) == true) {
        printf("player already connected");
        return;
    }
    // create entity
    std::string path = "./assets/r-typesheet42.png";
    entities.add(clientID, std::make_unique<E_Player>(path, 50, 50, 33.2, 17.2));
    auto& playerEntity = entities.get(clientID);
    // add entity to entities
    manager.getSystem<S_Renderer>()->addEntity(&playerEntity);
}

void server::Game::actionShootCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
{
    printf("shoot");
    if (entities.exists(clientID) == false) {
        printf("player not connected");
        return;
    }
    auto& playerEntity = entities.get(clientID);
    if (typeid(playerEntity) == typeid(E_Player)) {
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        playerEntity.newShoot("./assets/r-typesheet24.png", "missile", 10, transform->_position.x + 10, transform->_position.y + 2, transform->_size.x, transform->_size.y, 5, 0);
    }
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
    SparseArray<IEntity> entities;
    std::string path = "./assets/r-typesheet24.png";
    entities.add(10, std::make_unique<E_Enemy>(path, 700, 100, 65.2, 66));
    auto& ennemyEntity = entities.get(10);
    manager.getSystem<S_Renderer>()->addEntity(&ennemyEntity);
    int numClientID = 0;

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

            numClientID = std::stoi(clientID);
            //boucle sur mon tableau de pointeur sur fonctions
            auto it = _fonctions_map.find(command);
            if (it != _fonctions_map.end()) {
                auto fptr = it->second;
                (this->*fptr)(numClientID, manager, entities);
            } else {
                std::cout << "Commande not find." << std::endl;
            }

            _mutex_client.lock();
            if (entities.exists(numClientID) == false) {
                printf("player not connected");
                continue;
            }
            auto& playerEntity = entities.get(numClientID);
            _functions_client.push_back("POS " + std::to_string(Engine::getComponentRef<C_Transform>(playerEntity)->_position.x) + " " + std::to_string(Engine::getComponentRef<C_Transform>(playerEntity)->_position.y) + " " + clientID);
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


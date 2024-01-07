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

// void server::Game::actionQuitCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("quit\n");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         manager.getSystem<S_Renderer>()->removeEntity(&playerEntity);
//         entities.remove(clientID);
//     }
// }

// void server::Game::actionDamageCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("damage");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& entity = entities.get(clientID);
//     C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(entity);
//     C_Health *health = Engine::getComponentRef<C_Health>(entity);
//     if (health->_health <= 0) {
//         Engine::setHitboxStatus(entity, 2);
//         std::string dead_path = "./assets/r-typesheet1.png";
//         Image newImage = LoadImage(dead_path.c_str());
//         if (newImage.data == nullptr) {
//             std::cerr << "Erreur de chargement de l'image : " << dead_path << std::endl;
//         }
//         Engine::setSpriteImage(entity, newImage);
//         Texture2D newTexture = LoadTextureFromImage(newImage);
//         Engine::setSpriteTexture(entity, newTexture);
//         C_Transform *transform = Engine::getComponentRef<C_Transform>(entity);
//         Engine::setTransformSize(entity, {33.25, 345});
//         Engine::setTransformAni(entity, 0);
//     } else {
//         Engine::setHealth(entity, health->_health - 10);
//         Engine::setHitboxStatus(entity, 1);
//     }
// }

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
    printf("Game started\n");

    SystemManager manager;
    SparseArray<IEntity> entities;
    std::vector<Interaction> interaction_client;

    manager.addSystem<S_Collision>(entities);
    manager.addSystem<S_EnemyAI>(entities);

    entities.add(std::make_shared<E_Enemy>(700, 50, 65.2, 66), 2);
    auto& ennemyEntity = entities.get(2);

    int id = entities.add(std::make_shared<E_Enemy>(700, 350, 65.2, 66));
    auto& ennemyEntity3 = entities.get(id);

    int numClientID = 0;

    while (true) {
        _mutex.lock();
        if (_interaction_client.size() > 0) {
            interaction_client = _interaction_client;
            _interaction_client.clear();
        }
        _mutex.unlock();
        if (interaction_client.size() > 0) {
            for (auto interaction : interaction_client) {
                if (interaction.getConnect() == 1) {
                    printf("New Player with ID : %d\n", interaction.getClientID());
                    entities.add(std::make_shared<E_Player>(50, 50, 33.2, 17.2), interaction.getClientID());
                }
            }
        }

        _functions.clear();
        manager.update();
        // printf("tick++");
        _tick++;
        // printf("tick = " << _tick);

        //remplir la frame ici
        fillFrame(entities);
        interaction_client.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickSpeed));
    }
}

void server::Game::fillFrame(SparseArray<IEntity> entities)
{
    //remplir la frame ici
    Frame frame;

    frame.setArray(entities);

    frame.setTick(_tick);
    _mutex_frame.lock();
    _frames.push_back(frame);
    _mutex_frame.unlock();
}

// void server::Game::addFunction(std::string function)
// {
//     _mutex.lock();
//     _functions_server.push_back(function);
//     _mutex.unlock();
// }

std::vector<std::string> server::Game::getFunctionsClient()
{
    _mutex_client.lock();
    std::vector<std::string> functions = _functions_client;
    _functions_client.clear();
    _mutex_client.unlock();
    return functions;
}

// server::Frame& server::Frame::operator=(const Frame& other)
// {
//     _tick = other._tick;

//     return *this;
// }
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

// void server::Game::actionUpCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("up");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
//         if (transform) {
//             Engine::setTransformPos(playerEntity, {transform->_position.x, transform->_position.y - 10});
//             if (transform->_animation == 3) {
//                 Engine::setTransformAni(playerEntity, 4);
//             } else if (transform->_animation == 2) {
//                 Engine::setTransformAni(playerEntity, 1);
//             } else if (transform->_animation == 1) {
//                 Engine::setTransformAni(playerEntity, 0);
//             } else if (transform->_animation == 0) {
//                 Engine::setTransformAni(playerEntity, 3);
//             } else {
//                 Engine::setTransformAni(playerEntity, 4);
//             }
//         }
//     }
// }

// void server::Game::actionDownCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("down");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
//         if (transform) {
//             Engine::setTransformPos(playerEntity, {transform->_position.x, transform->_position.y + 10});
//             if (transform->_animation == 1) {
//                 Engine::setTransformAni(playerEntity, 2);
//             } else if (transform->_animation == 4) {
//                 Engine::setTransformAni(playerEntity, 3);
//             } else if (transform->_animation == 3) {
//                 Engine::setTransformAni(playerEntity, 0);
//             } else if (transform->_animation == 0) {
//                 Engine::setTransformAni(playerEntity, 1);
//             } else {
//                 Engine::setTransformAni(playerEntity, 2);
//             }
//         }
//     }
// }

// void server::Game::actionLeftCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("left");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
//         if (transform) {
//             Engine::setTransformPos(playerEntity, {transform->_position.x - 10, transform->_position.y});
//             if (transform->_animation == 2) {
//                 Engine::setTransformAni(playerEntity, 1);
//             } else if (transform->_animation == 4) {
//                 Engine::setTransformAni(playerEntity, 3);
//             } else {
//                 Engine::setTransformAni(playerEntity, 0);
//             }
//         }
//     }
// }

// void server::Game::actionRightCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("right");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
//         if (transform) {
//             Engine::setTransformPos(playerEntity, {transform->_position.x + 10, transform->_position.y});
//             if (transform->_animation == 2) {
//                 Engine::setTransformAni(playerEntity, 1);
//             } else if (transform->_animation == 4) {
//                 Engine::setTransformAni(playerEntity, 3);
//             } else {
//                 Engine::setTransformAni(playerEntity, 0);
//             }
//         }
//     }
// }

// void server::Game::actionDebugCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("debug\n");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         printf("Player ID : %d\n", clientID);
//         printf("Player Position : %f, %f\n", Engine::getComponentRef<C_Transform>(playerEntity)->_position.x, Engine::getComponentRef<C_Transform>(playerEntity)->_position.y);
//     }
// }

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

// void server::Game::actionConnectCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("connection\n");
//     int nbrPlayer = 0;
//     const auto& sparseIds = entities.getAllIndices();
//     for (auto id : sparseIds) {
//         if (id != -1) {
//             auto& tmpEntity = entities.get(id);
//             if (typeid(tmpEntity) == typeid(E_Player)) {
//                 nbrPlayer++;
//             }
//         }
//     }
//     if (nbrPlayer >= 4)
//         return;
//     if (entities.exists(clientID) == true) {
//         printf("player already connected");
//         return;
//     }
//     // create entity
//     std::string path = "./assets/r-typesheet42.png";
//     entities.add(std::make_unique<E_Player>(path, 50, 50, 33.2, 17.2), clientID);
//     auto& playerEntity = entities.get(clientID);
//     // add entity to entities
//     manager.getSystem<S_Renderer>()->addEntity(&playerEntity);
// }

// void server::Game::actionShootCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("shoot");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     E_Player& playerEntity = static_cast<E_Player&>(entities.get(clientID));
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
//         playerEntity.newShoot("./assets/r-typesheet24.png", 10, transform->_position.x + 10, transform->_position.y + 2, transform->_size.x, transform->_size.y, 5, 0);
//     }
//     auto effect = manager.getSystem<S_AudioManager>()->getSoundEffect().find("SHOOT");
//     PlaySound(effect->second);
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

// void server::Game::actionScoreCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
// {
//     printf("score");
//     if (entities.exists(clientID) == false) {
//         printf("player not connected");
//         return;
//     }
//     auto& playerEntity = entities.get(clientID);
//     if (typeid(playerEntity) == typeid(E_Player)) {
//         C_Score *score = Engine::getComponentRef<C_Score>(playerEntity);
//         Engine::setScore(playerEntity, score->_score + 10);
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
    printf("Game started");

    SystemManager manager;

    // To Remove
    manager.addSystem<S_Renderer>(800, 600, 60, "debug", "./assets/background.png");
    manager.addSystem<S_AudioManager>();
    manager.addSystem<S_Collision>();

    SparseArray<IEntity> entities;
    std::string path = "./assets/r-typesheet24.png";
    entities.add(std::make_unique<E_Enemy>(path, 700, 100, 65.2, 66), 10);
    auto& ennemyEntity = entities.get(10);
    manager.getSystem<S_Renderer>()->addEntity(&ennemyEntity);
    int numClientID = 0;

    // parse the entities in the sparse array and add them to the collision system
    const auto& sparseIds = entities.getAllIndices();
    for (auto id : sparseIds) {
        if (id != -1) {
            auto& tmpEntity = entities.get(id);
            manager.getSystem<S_Collision>()->addEntity(&tmpEntity);
        }
    }

    // To Remove
    auto backgroundMusic = manager.getSystem<S_AudioManager>()->getBackgroundMusic().find("THEME");
    PlayMusicStream(backgroundMusic->second);

    while (true) {
        // _mutex.lock();
        // if (_functions_server.size() > 0) {
        //     _functions = _functions_server;
        //     _functions_server.clear();
        // }
        // _mutex.unlock();
        // To Remove
        UpdateMusicStream(backgroundMusic->second);

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
                std::cout << "Commande not found." << std::endl;
            }

            if (entities.exists(numClientID) == false) {
                printf("Player not connected");
                continue;
            }
            auto& playerEntity = entities.get(numClientID);
            manager.getSystem<S_Collision>()->addEntity(&playerEntity);
            _mutex_client.lock();
            _functions_client.push_back("POS " + std::to_string(Engine::getComponentRef<C_Transform>(playerEntity)->_position.x) + " " + std::to_string(Engine::getComponentRef<C_Transform>(playerEntity)->_position.y) + " " + clientID);
            _mutex_client.unlock();
        }
        _functions.clear();
        manager.update();
        // printf("tick++");
        _tick++;
        // printf("tick = " << _tick);

        //remplir la frame ici
        fillFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickSpeed));
    }
}

void server::Game::fillFrame()
{
    //remplir la frame ici
    Frame frame;

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

server::Frame& server::Frame::operator=(const Frame& other)
{
    _tick = other._tick;
    return *this;
}
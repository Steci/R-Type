/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include "../include/System.hpp"

void ASystem::addEntity(IEntity* entity) {
    _entities.push_back(entity);
}

void ASystem::removeEntity(IEntity* entity) {
    for (auto it = _entities.begin(); it != _entities.end(); it++) {
        if (*it == entity) {
            _entities.erase(it);
            return;
        }
    }
}

void SystemManager::update()
{
    for (auto& system : _systems) {
        system->update();
    }
}

S_Renderer::S_Renderer(int w, int h, int fps, std::string wName) {
    _screenWidth = w;
    _screenHeight = h;
    _targetFps = fps;
    _windowName = wName;
    InitWindow(_screenWidth, _screenHeight, _windowName.c_str());
    SetTargetFPS(_targetFps);
};

void S_Renderer::render()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        for (auto& entity : _entities) {
            entity->render();
        }
    EndDrawing();
}

void S_Renderer::update()
{
    if (IsKeyPressed(KEY_ESCAPE))
        closeWindow();
    if (!WindowShouldClose())
        render();
}

void S_Renderer::closeWindow()
{
    CloseWindow();
}

bool S_Collision::checkCollision(IEntity* entity1, IEntity* entity2)
{
    C_Hitbox *hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);
    C_Hitbox *hitbox2 = Engine::getComponentRef<C_Hitbox>(*entity2);
    C_Transform *transform1 = Engine::getComponentRef<C_Transform>(*entity1);
    C_Transform *transform2 = Engine::getComponentRef<C_Transform>(*entity2);

    if (transform1->_position.x < transform2->_position.x + hitbox2->_size.x &&
        transform1->_position.x + hitbox1->_size.x > transform2->_position.x &&
        transform1->_position.y < transform2->_position.y + hitbox2->_size.y &&
        transform1->_position.y + hitbox1->_size.y > transform2->_position.y)
        return true;
    return false;
};

int S_EventManager::EventKeyPressed(std::list<int> keys)
{
    for (auto key: keys) {
        if (IsKeyPressed(key)) {
            return key;
        }
    }
    return -1;
}
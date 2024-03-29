/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include "EngineSystem.hpp"

void System::addEntity(IEntity* entity) {
    _entities.push_back(entity);
}

void System::removeEntity(IEntity* entity) {
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

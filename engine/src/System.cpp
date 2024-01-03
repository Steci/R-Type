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

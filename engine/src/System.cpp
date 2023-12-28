/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include "System.hpp"

void SystemManager::update()
{
    for (auto& system : _systems) {
        system->update();
    }
}
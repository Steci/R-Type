/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include "Engine.hpp"

int main(void)
{
    SystemManager manager;

    manager.addSystem<S_Renderer>(800, 600, 60, "Window Name");
    manager.getSystem<S_Renderer>()->addEntity(std::make_unique<E_Enemy>("assets/placeholder.png"));

    while (1) {
        manager.update();
    };

    return (0);
}

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include "Engine.hpp"

int main(void)
{
    std::cout << "Engine Lib" << std::endl;

    SystemManager manager;

    manager.addSystem<S_Renderer>(800, 600, 60, "Window Name");

    while (1) {
        manager.update();
    };

    return (0);
}

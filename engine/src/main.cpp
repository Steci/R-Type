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

    std::unique_ptr<S_Renderer> renderer = std::make_unique<S_Renderer>(800, 600, 60, "Window Name");
    manager.addSystem(std::move(renderer));

    while (1) {
        manager.update();
    };

    return (0);
}

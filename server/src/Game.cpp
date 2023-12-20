/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "Game.hpp"

server::Game::Game()
{
    _tick = 0;
}

server::Game::~Game()
{
}

void server::Game::run()
{
    std::cout << "Game started" << std::endl;
    SystemManager manager;
    auto tickDuration = std::chrono::microseconds(1000000) / 66;
    auto nextTickTime = std::chrono::high_resolution_clock::now() + tickDuration;

    while (true) {
        auto currentTime = std::chrono::high_resolution_clock::now();

        if (currentTime >= nextTickTime) {
            manager.update();
            _tick++;
            nextTickTime += tickDuration;
        }
    }
}

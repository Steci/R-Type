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
    std::string action;

    while (true) {
        _mutex.lock();
        if (functions.size() > 0) {
            action = functions[0];
            functions.erase(functions.begin());
        }
        _mutex.unlock();
        manager.update();
        _tick++;
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickSpeed));
    }
}
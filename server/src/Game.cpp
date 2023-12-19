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
    SparseArray<IEntity> entities;

    // std::cout << "start loop" << std::endl;
    while (true) {
        // std::cout << "lock mutex" << std::endl;
        _mutex.lock();
        // std::cout << "check if queue is not empty" << std::endl;
        if (_functions_server.size() > 0) {
            // std::cout << "discharge queue" << std::endl;
            _functions = _functions_server;
            _functions_server.clear();
        }
        // std::cout << "unlock mutex" << std::endl;
        _mutex.unlock();
        // std::cout << "loop functions" << std::endl;
        for (auto& function : _functions) {
            std::cout << "function = " << function << std::endl;
        }
        // std::cout << "clear functions" << std::endl;
        _functions.clear();
        // std::cout << "update manager" << std::endl;
        manager.update();
        // std::cout << "tick++" << std::endl;
        _tick++;
        // std::cout << "tick = " << _tick << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickSpeed));
    }
}

void server::Game::addFunction(std::string function)
{
    _mutex.lock();
    _functions_server.push_back(function);
    _mutex.unlock();
}
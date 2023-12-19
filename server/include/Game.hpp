/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.hpp
*/

#pragma once

#include "../../engine/include/Engine.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <map>

#define TICK_SPEED 15

namespace server
{
    class Game
    {
        public:
            Game();
            ~Game();
            void run();
            void addFunction(std::string function);
            std::vector<std::string> getFunctions() {return _functions;}

        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex;
            std::vector<std::string> _functions_server;
            // std::map<int, Key> m{{KEY_A, Key}, {KEY_RIGHT, Key}, {KEY_LEFT, Key}, {KEY_DOWN, Key}, {KEY_ESCAPE, Key}};
            typedef void (*Key)(int button);
            std::vector<std::string> _functions;
    };
}

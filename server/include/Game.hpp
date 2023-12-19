/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.hpp
*/

#pragma once

#include <iostream>
#include <thread>

#define TICK_SPEED 15

namespace server
{
    class Game
    {
        public:
            Game();
            ~Game();
            void run();

        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
    };
}

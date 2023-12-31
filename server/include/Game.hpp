/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.hpp
*/

#pragma once

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <map>

#define TICK_SPEED 15

namespace server
{
    class Game
    {
        typedef void (Game::*functionsExecution)(int, SystemManager, SparseArray<IEntity>&);

        public:
            Game();
            ~Game();
            void run();
            void addFunction(std::string function);
            std::vector<std::string> getFunctions() {return _functions;}
            std::pair<std::string, std::string> parseCommand(const std::string& input);
            std::vector<std::string> getFunctionsClient();
            void actionUpCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionDownCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionLeftCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionRightCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionDebugCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionQuitCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionConnectCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionShootCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionDamageCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);
            void actionDeadCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities);


        private:
            int _tickSpeed = TICK_SPEED;
            int _tick;
            std::mutex _mutex;
            std::vector<std::string> _functions_server;
            // std::map<int, Key> m{{KEY_A, Key}, {KEY_RIGHT, Key}, {KEY_LEFT, Key}, {KEY_DOWN, Key}, {KEY_ESCAPE, Key}};
            typedef void (*Key)(int button);
            std::vector<std::string> _functions;
            std::vector<std::string> _functions_client;
            std::mutex _mutex_client;
            std::map<std::string, functionsExecution> _fonctions_map;
    };
}

/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.hpp
*/

#pragma once

#include "Network.hpp"
#include <iostream>
#include <thread>

namespace server {
    class Server {
        public:
            Server(int port, int maxClients): _network(port, maxClients) {};
            ~Server() {};
            int run();

        private:
            Network _network;

            std::thread _gameThread;
            std::thread _checkClientsThread;
    };
}
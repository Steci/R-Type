/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client.hpp
*/

#pragma once

#include "Network.hpp"

namespace client {
    class Client {
        public:
            Client(std::string serverIP, int port): _network(serverIP, port) {};
            ~Client() {};
            int run();
        private:
            Network _network;
            // Game _game;
    };
}

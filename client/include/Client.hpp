/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client.hpp
*/

#pragma once

#include "Network.hpp"
#include "Game.hpp"

namespace client {
    class Client {
        public:
            Client(std::string serverIP, int port): _network(serverIP.empty() ? "127.0.0.1" : serverIP, validatePort(port)) {};
            ~Client() {};


            int validatePort(int port);
            int run();
        private:
            Network _network;
            // Game _game;
    };
}

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

    /**
     * @brief Server class
     * 
     */
    class Server {
        public:
            /**
             * @brief Construct a new Server object
             * 
             * @param port is the port of the server
             * @param maxClients is the max number of clients
             */
            Server(int port, int maxClients): _network(port, maxClients) {};

            /**
             * @brief Destroy the Server object
             * 
             */
            ~Server() {};

            /**
             * @brief run the server
             * 
             * @return int is the return value
             */
            int run();

        private:
            Network _network;

            std::thread _gameThread;
            std::thread _checkClientsThread;
    };
}

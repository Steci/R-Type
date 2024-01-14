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
    /**
     * @brief Client class
     * 
     */
    class Client {
        public:
            /**
             * @brief Construct a new Client object
             * 
             * @param serverIP is the server IP
             * @param port is the port to connect to
             */
            Client(std::string serverIP, int port): _network(serverIP.empty() ? "127.0.0.1" : serverIP, validatePort(port)) {};

            /**
             * @brief Destroy the Client object
             * 
             */
            ~Client() {};


            /**
             * @brief Validate the port
             * 
             * @param port is the port to validate
             * @return int is the port validated
             */
            int validatePort(int port);

            /**
             * @brief Run the client
             * 
             * @return int is the return value
             */
            int run();
        private:
            Network _network;
            // Game _game;
    };
}

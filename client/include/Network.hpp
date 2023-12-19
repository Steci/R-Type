/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network.hpp
*/

#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

namespace client {
    class Network {
        public:
            Network(std::string serverIP, int port);
            ~Network();
            void run();
        private:
            std::string _serverIP;
            int _port;
            bool _isRunning = true;
            int _fd;
            fd_set _readFds;
            struct sockaddr_in _addr;

            int fillSocket();
            int fillAddr();
            int bindSocket();
    };

}

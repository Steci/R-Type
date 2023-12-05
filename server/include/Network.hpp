/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.hpp
*/

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <bitset>

namespace server {
    class Client {
        public:
            Client(int fd, int id, std::string name): _fd(fd), _id(id), _name(name) {};
            ~Client() {};
            int getFd() const {return _fd;};
            int getId() const {return _id;};
            std::string getName() const {return _name;};

        private:
            int _fd;
            int _id;
            const std::string _name;
    };

    class Network {
        public:
            Network(int port, int maxClients);
            ~Network();
            void run();
        private:
            int _port;
            unsigned int _maxClients;
            bool _isRunning = true;
            int _fd;
            int _maxFd;
            fd_set _readFds;
            struct sockaddr_in _addr;
            std::vector<Client> _clients;

            int fillSocket();
            int fillAddr();
            int bindSocket();
            int setMaxFd();
            int handleNewConnection();
            int handleClient();
    };
}

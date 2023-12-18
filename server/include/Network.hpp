/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.hpp
*/

#pragma once

#ifdef linux
    #include <sys/socket.h>
    #include <netinet/in.h>
    #define OS "linux"
#endif

#ifdef _WIN64
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #define OS "windows"
#endif

#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <bitset>
#include <fstream>
#include <algorithm>

namespace server {
    class Client {
        public:
            Client(int fd, int id, std::string name): _fd(fd), _id(id), _name(name) {};
            ~Client() {};
            int getFd() const {return _fd;};
            int getId() const {return _id;};
            std::string getName() const {return _name;};
            int readClient();
            bool operator==(const Client& other) const;
            Client& operator=(const Client& other);

        private:
            int _fd;
            int _id;
            bool _isConnected = true;
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
            #ifdef linux
                struct sockaddr_in _addr;
            #endif
            #ifdef _WIN64
                SOCKADDR_IN _addr;
            #endif
            std::vector<Client> _clients;

            int fillSocket();
            int fillAddr();
            int bindSocket();
            int setMaxFd();
            int handleNewConnection();
            int handleClient();
    };
}

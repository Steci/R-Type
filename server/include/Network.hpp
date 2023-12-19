/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.hpp
*/

#pragma once

#include "Game.hpp"

#ifdef linux
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
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
#include <cstring>
#include <netdb.h>
#include <chrono>

namespace server {
    class Client {
        public:
            #ifdef linux
                Client(struct sockaddr_in addr, int id, std::string name): _addr(addr), _id(id), _name(name) {};
                struct sockaddr_in getAddr() const {return _addr;};
            #endif
            ~Client() {};
            int getId() const {return _id;};
            std::string getName() const {return _name;};
            bool operator==(const Client& other) const;
            Client& operator=(const Client& other);

        private:
            #ifdef linux
                struct sockaddr_in _addr;
            #endif
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
            #ifdef linux
                struct sockaddr_in _addr;
                struct sockaddr_in _clientAddr;
                socklen_t _clientAddrLen;
            #endif
            #ifdef _WIN64
                SOCKADDR_IN _addr;
            #endif
            int _tickrate;
            std::vector<Client> _clients;
            Game _game;

            int fillSocket();
            int fillAddr();
            int bindSocket();
            int handleNewConnection();
            int handleClient(std::string message);
            int handleClientMessage(std::string message, int client_id);

            // Commands
            int commandKill();
            int commandKick(int client_id, std::string message);
            int commandSetTickrate() const;
            int commandPing(int client_id) const;
            int commandError(int client_id, std::string error) const;
    };
}

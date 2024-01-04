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
#include <sstream>

namespace server {
    class Test {
        public:
            Test() = default;
            ~Test() = default;
            int getTick() const {return _Tick;};
            int getTickspeed() const {return _Tickspeed;};
            void setTick(int tick) {_Tick = tick;};
            void setTickspeed(int tickspeed) {_Tickspeed = tickspeed;};
            std::vector<char> serialize() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Test));
            }
            void deserialize(const std::vector<char>& serializedData) {
                // if (serializedData.size() != sizeof(Test)) {
                //     throw std::runtime_error("Invalid data size for deserialization");
                // }
                *this = *reinterpret_cast<const Test*>(serializedData.data());
            }
        private:
            int _Tick = 10;
            int _Tickspeed = 1100;
    };
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
            void run(Game *game);
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
            std::vector<std::string> _commands = {"CONNECT", "QUIT", "UP", "DOWN", "LEFT", "RIGHT", "DEBUG", "SHOOT", "DAMAGE", "SCORE"};

            int fillSocket();
            int fillAddr();
            int bindSocket();
            int handleNewConnection();
            int handleClient(std::string message);
            std::string handleClientMessage(std::string message, int client_id);
            void manageMessage(std::string message, int client_id, Game *game);
            void updateClients(int client_id, std::string message, Game *game);

            // Commands
            int commandKill();
            int commandKick(int client_id, std::string message);
            int commandSetTickrate(std::vector<char> data) const;
            int commandPing(int client_id) const;
            int commandError(int client_id, std::string error) const;
    };
}

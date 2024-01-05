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

            std::vector<char> serializeTick() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Test));
            }
            void deserializeTick(const std::vector<char>& serializedData) {
                // if (serializedData.size() != sizeof(Test)) {
                //     throw std::runtime_error("Invalid data size for deserialization");
                // }
                *this = *reinterpret_cast<const Test*>(serializedData.data());
            }



        private:
            int _Tick = 10;
            int _Tickspeed = 1100;
    };

    class Serialize {
        public:
            Serialize() = default;
            ~Serialize() = default;

            std::string deserialize(const std::vector<char>& data) {
                return std::string(data.begin(), data.end());
            }

            std::vector<char> serialize(const std::string& data) {
                return std::vector<char>(data.begin(), data.end());
            }

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

    class Connection {
        public:
            Connection() {};
            ~Connection() {};
            int getConnect() const {return _connect;};
            int getConnected() const {return _connected;};
            int setConnected(int connected) {_connected = connected;};
            std::vector<char> serializeConnection() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Connection));
            }
            void deserializeConnection(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Connection*>(serializedData.data());
            }
        private:
            int _connect;
            int _connected;
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
            std::vector<std::string> _commands = {"CONNECT", "QUIT", "INPUT", "UP", "DOWN", "LEFT", "RIGHT", "DEBUG", "SHOOT", "DAMAGE", "SCORE"};

            int fillSocket();
            int fillAddr();
            int bindSocket();
            int handleNewConnection(Connection Connect);
            int handleClient(std::vector<char> buffer);
            std::string handleClientMessage(std::string message, int client_id);
            void manageMessage(std::string message, int client_id, Game *game);
            void updateClients(int client_id, std::string message, Game *game);
            void checkClass(std::vector<char> buffer);

            // Commands
            int commandKill(std::string data);
            int commandKick(std::string data, int client_id);
            int commandSetTickrate(std::string data) const;
            int commandPing(std::string data, int client_id) const;
            int commandError(std::string data, int client_id) const;
    };

    namespace Errors {
        class Error : public std::exception {
            public:
                Error(const std::string &message) {_message += message;};
                ~Error() throw() {};
                virtual const char *what() const throw() {return _message.c_str();};
            protected:
                std::string _message = "Error: ";
        };

        class WrongClass : public Error {
            public:
                WrongClass(const std::string &message) : Error(message) {};
                ~WrongClass() {};
        };
    }
}

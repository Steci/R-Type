/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.hpp
*/


#include "Game.hpp"

#ifdef linux
    #pragma once
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define OS "linux"
#endif

#ifdef _WIN64
    #pragma comment(lib, "Ws2_32.lib")
    #define NOGDI
    #define NOUSER
    #define MMNOSOUND
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <io.h>
    #include <process.h>
    #define OS "windows"
#endif

#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <sstream>
#include <tuple>

namespace server {
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
            #ifdef _WIN64
                Client(struct sockaddr_in addr, int id, std::string name): _addr(addr), _id(id), _name(name) {};
                struct sockaddr_in getAddr() const {return _addr;};
            #endif
            ~Client() {};
            int getId() const {return _id;};
            std::string getName() const {return _name;};
            bool operator==(const Client& other) const;
            Client& operator=(const Client& other);
            void setGameId(int gameId) {_gameId = gameId;};
            int getGameId() const {return _gameId;};

        private:
            #ifdef linux
                struct sockaddr_in _addr;
            #endif
            #ifdef _WIN64
                struct sockaddr_in _addr;
            #endif
            int _id;
            int _gameId = -1;
            bool _isConnected = true;
            const std::string _name;
    };

    class Connection {
        public:
            Connection() {};
            ~Connection() {};
            int getConnect() const {return _connect;};
            int getConnected() const {return _connected;};
            void setConnected(int connected) {_connected = connected;};
            void setId(int id) {_id = id;};
            int getId() const {return _id;};
            std::vector<char> serializeConnection() {
                const char* data = reinterpret_cast<const char*>(this);
                return std::vector<char>(data, data + sizeof(Connection));
            }
            void deserializeConnection(const std::vector<char>& serializedData) {
                *this = *reinterpret_cast<const Connection*>(serializedData.data());
            }
            Connection& operator=(const Connection& other) {
                _connect = other._connect;
                _connected = other._connected;
                _id = other._id;
                return *this;
            }
        private:
            int _connect;
            int _connected;
            int _id;
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
                struct sockaddr_in _addr;
                struct sockaddr_in _clientAddr;
                socklen_t _clientAddrLen;
                WSADATA _wsaData;
            #endif
            int _tickrate;
            int _last_tick_send = 0;
            std::vector<Client> _clients;
            Game _game;
            std::vector<std::string> _commands = {"CONNECT", "QUIT", "INPUT", "UP", "DOWN", "LEFT", "RIGHT", "DEBUG", "SHOOT", "DAMAGE", "SCORE"};

            int fillSocket();
            int fillAddr();
            int bindSocket();
            std::tuple<int, server::Connection> handleNewConnection(Connection Connect);
            std::tuple<int, server::Connection> handleClient(std::vector<char> buffer);
            std::string handleClientMessage(std::string message, int client_id);
            void manageMessage(std::string message, int client_id, Game *game);
            void updateClients(int client_id, Game *game);
            void checkClass(std::vector<char> buffer);
            int CreateGame(std::vector<int> idNotUsableGame);

            // Commands
            int commandKill(std::string data);
            int commandKick(std::string data, int client_id);
            int commandSetTickrate(std::string data) const;
            int commandPing(std::string data, int client_id) const;
            int commandError(std::string data, int client_id) const;
            void manageClient(std::vector<char> buffer, int client_id, Game *game);
    };
}

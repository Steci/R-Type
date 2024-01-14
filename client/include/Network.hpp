/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network.hpp
*/


#ifdef __linux__
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

#include "Game.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <sstream>

namespace client {
    class Game;
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

    class Network {
        public:
            Network(std::string serverIP, int serverPort);
            ~Network();
            void run(Game *game);
            int connectCommand(Game *game, int createGame = -1, int joinGame = -1, int gameId = -1);
        private:
            std::string _serverIP;
            int _serverPort;
            bool _isRunning = true;
            int _fd;
            #ifdef __linux__
                struct sockaddr_in _addr;
                struct sockaddr_in _serverAddr;
                socklen_t _serverAddrLen;
            #endif
            #ifdef _WIN64
                struct sockaddr_in _addr;
                struct sockaddr_in _serverAddr;
                socklen_t _serverAddrLen;
                WSADATA _wsaData;
            #endif
            int _tickrate;
            std::vector<std::string> _commands = {"KILL", "KICK", "SET_TICKRATE", "UPDATE", "ERROR"};
            std::vector<std::string> _inputs = {"UP", "DOWN", "LEFT", "RIGHT", "SHOOT", "DAMAGE", "SCORE"};
            int _clientID;

            int fillSocket();
            int fillAddr();
            int bindSocket();
            int getRandomPort();

            std::string inputHandle(std::string input);

            // Commands Send to the server
            int inputCommand(std::string input);

            void handleCommands(std::vector<char> buffer, Game *game);

            void checkInteraction(Game *game);
    };

    class Connection : public AConnection {
        public:
            Connection() {};
            ~Connection() {};
    };
}

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network.hpp
*/

#pragma once

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
#include <thread>
#include <cstdlib>
#include <ctime>
#include <sstream>

namespace client {
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
            int _Tickspeed = 1000;
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

    class Network {
        public:
            Network(std::string serverIP, int serverPort);
            ~Network();
            void run();
            int connectCommand();
        private:
            std::string _serverIP;
            int _serverPort;
            bool _isRunning = true;
            int _fd;
            #ifdef linux
                struct sockaddr_in _addr;
                struct sockaddr_in _serverAddr;
                socklen_t _serverAddrLen;
            #endif
            #ifdef _WIN64
                SOCKADDR_IN _addr;
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
            int disconnectCommand();
            int pingCommand();
            int inputCommand(std::string input);

            std::string handleCommands(std::string message);
    };

}

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
    /**
     * @brief Game class
     * 
     */
    class Game;


    /**
     * @brief Serialize class
     * 
     */
    class Serialize {
        public:
            /**
             * @brief Construct a new Serialize object
             * 
             */
            Serialize() = default;

            /**
             * @brief Destroy the Serialize object
             * 
             */
            ~Serialize() = default;

            /**
             * @brief Deserialize the data.
             * 
             * @param data is the data.
             * @return std::string is the string of the data.
             */
            std::string deserialize(const std::vector<char>& data) {
                return std::string(data.begin(), data.end());
            }

            /**
             * @brief Serialize the data.
             * 
             * @param data is the data.
             * @return std::vector<char> is the vector of the data.
             */
            std::vector<char> serialize(const std::string& data) {
                return std::vector<char>(data.begin(), data.end());
            }

    };

    /**
     * @brief Network class
     * 
     */
    class Network {
        public:
            /**
             * @brief Construct a new Network object
             * 
             * @param serverIP is the server IP.
             * @param serverPort is the server port.
             */
            Network(std::string serverIP, int serverPort);

            /**
             * @brief Destroy the Network object
             * 
             */
            ~Network();
            
            /**
             * @brief Run the network.
             * 
             * @param game is the game.
             * @param gameThread is the game thread.
             */
            void run(Game *game, std::thread *gameThread);

            /**
             * @brief Connect to the server.
             * 
             * @param game is the game.
             * @param createGame is the create game.
             * @param joinGame is the join game.
             * @param gameId is the game id.
             * @return int is the connect command.
             */
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

            /**
             * @brief Fill the socket.
             * 
             * @return int is the fill socket.
             */
            int fillSocket();

            /**
             * @brief Fill the address.
             * 
             * @return int is the fill address.
             */
            int fillAddr();

            /**
             * @brief Bind the socket.
             * 
             * @return int is the bind socket.
             */
            int bindSocket();

            /**
             * @brief Get the Random Port object
             * 
             * @return int is the random port.
             */
            int getRandomPort();

            /**
             * @brief Handle the input.
             * 
             * @param input is the input.
             * @return std::string is the input.
             */
            std::string inputHandle(std::string input);

            /**
             * @brief Input the command.
             * 
             * @param input is the input command.
             * @return int is the input command.
             */
            int inputCommand(std::string input);

            /**
             * @brief Handle the commands.
             * 
             * @param buffer is the buffer.
             * @param game is the game.
             */
            void handleCommands(std::vector<char> buffer, Game *game);

            /**
             * @brief Handle the inputs.
             * 
             * @param game is the game.
             */
             */
            void checkInteraction(Game *game);
    };


    /**
     * @brief Serialize class
     * 
     */
    class Connection : public AConnection {
        public:
            /**
             * @brief Construct a new Connection object
             * 
             */
            Connection() {};

            /**
             * @brief Destroy the Connection object
             * 
             */
            ~Connection() {};
    };
}

/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.hpp
*/


#include "Game.hpp"

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
             * @brief Deserialize the data
             * 
             * @param data is the data to deserialize
             * @return std::string is the serialized data
             */
            std::string deserialize(const std::vector<char>& data) {
                return std::string(data.begin(), data.end());
            }

            /**
             * @brief Serialize the data
             * 
             * @param data is the data to serialize
             * @return std::vector<char> is the serialized data
             */
            std::vector<char> serialize(const std::string& data) {
                return std::vector<char>(data.begin(), data.end());
            }

    };

    /**
     * @brief Client class
     * 
     */
    class Client {
        public:
            #ifdef __linux__
                /**
                 * @brief Construct a new Client object
                 * 
                 * @param addr is the address of the client
                 * @param id is the id of the client
                 * @param name is the name of the client
                 */
                Client(struct sockaddr_in addr, int id, std::string name): _addr(addr), _id(id), _name(name), _gameId(-1) {};
                struct sockaddr_in getAddr() const {return _addr;};
            #endif
            #ifdef _WIN64
                /**
                 * @brief Construct a new Client object
                 * 
                 * @param addr is the address of the client
                 * @param id is the id of the client
                 * @param name is the name of the client
                 */
                Client(struct sockaddr_in addr, int id, std::string name): _addr(addr), _id(id), _name(name), _gameId(-1) {};
                struct sockaddr_in getAddr() const {return _addr;};
            #endif

            /**
             * @brief Destroy the Client object
             * 
             */
            ~Client() {};

            /**
             * @brief Get the Id object
             * 
             * @return int is the id of the client
             */
            int getId() const {return _id;};

            /**
             * @brief Get the Name object
             * 
             * @return std::string is the name of the client
             */
            std::string getName() const {return _name;};

            /**
             * @brief Operator == to compare two clients
             * 
             * @param other is the other client to compare
             * @return true if the clients are the same
             * @return false if the clients are not the same
             */
            bool operator==(const Client& other) const;

            /**
             * @brief Operator = to assign a client to another
             * 
             * @param other is the other client to assign
             * @return Client& is the client assigned
             */
            Client& operator=(const Client& other);

            /**
             * @brief Get the Is Connected object
             * 
             * @return true if the client is connected
             * @return false if the client is not connected
             */
            void setGameId(int gameId) {_gameId = gameId;};

            /**
             * @brief Get the Is Connected object
             * 
             * @return true if the client is connected
             * @return false if the client is not connected
             */
            int getGameId() const {return _gameId;};

        private:
            #ifdef __linux__
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

    /**
     * @brief Connection class
     * 
     */
    class Connection : public AConnection{
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

    /**
     * @brief Protocole class
     * 
     */
    class Protocole : AProtocole {
        public:
            /**
             * @brief Construct a new Protocole object
             * 
             */
            Protocole() {};

            /**
             * @brief Destroy the Protocole object
             * 
             */
            ~Protocole() {};
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
             * @param port 
             * @param maxClients 
             */
            Network(int port, int maxClients);

            /**
             * @brief Destroy the Network object
             * 
             */
            ~Network();
            
            /**
             * @brief Run the network
             * 
             */
            void run();
        private:
            int _port;
            unsigned int _maxClients;
            bool _isRunning = true;
            int _fd;
            #ifdef __linux__
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
            std::vector<Client> _clients;
            Game _game;
            std::vector<std::string> _commands = {"CONNECT", "QUIT", "INPUT", "UP", "DOWN", "LEFT", "RIGHT", "DEBUG", "SHOOT", "DAMAGE", "SCORE"};

            /**
             * @brief Fill the socket
             * 
             * @return int is the socket
             */
            int fillSocket();

            /**
             * @brief Fill the address
             * 
             * @return int is the address
             */
            int fillAddr();

            /**
             * @brief Bind the socket
             * 
             * @return int is the bind socket
             */
            int bindSocket();

            /**
             * @brief Handle the new connection
             * 
             * @param Connect is the connection to handle
             * @return std::tuple<int, server::Connection> is the tuple of the connection
             */
            std::tuple<int, server::Connection> handleNewConnection(Connection Connect);

            /**
             * @brief Handle the client
             * 
             * @param buffer is the buffer to handle
             * @return std::tuple<int, server::Connection> is the tuple of the connection
             */
            std::tuple<int, server::Connection> handleClient(std::vector<char> buffer);

            /**
             * @brief Handle the client message
             * 
             * @param message is the message to handle
             * @param client_id is the id of the client
             * @return std::string is the message handled
             */
            std::string handleClientMessage(std::string message, int client_id);

            /**
             * @brief Update the clients
             * 
             * @param game is the game to update
             */
            void updateClients(std::unique_ptr<Game> *game);

            /**
             * @brief Handle the inputs
             * 
             * @param game is the game to handle
             */
            void checkClass(std::vector<char> buffer);

            /**
             * @brief Handle the inputs
             * 
             * @param game is the game to handle
             */
            int CreateGame(std::vector<int> idNotUsableGame);

            /**
             * @brief Handle the inputs
             * 
             * @param data is the data to handle
             * @return int is the command
             */
            int commandKill(std::string data);

            /**
             * @brief Handle the inputs
             * 
             * @param data is the data to handle
             * @return int is the command
             */
            int commandKick(std::string data, int client_id);

            /**
             * @brief Handle the inputs
             * 
             * @param data is the data to handle
             * @return int is the command
             */
            int commandSetTickrate(std::string data) const;

            /**
             * @brief Handle the inputs
             * 
             * @param data is the data to handle
             * @param client_id is the id of the client
             * @return int is the command
             */
            int commandPing(std::string data, int client_id) const;

            /**
             * @brief Handle the inputs
             * 
             * @param data is the data to handle
             * @param client_id is the id of the client
             * @return int is the command
             */
            int commandError(std::string data, int client_id) const;

            /**
             * @brief Handle the inputs
             * 
             * @param data is the data to handle
             * @param client_id is the id of the client
             * @return int is the command
             */
            Interaction manageClient(std::vector<char> buffer, int client_id, Game *game);
    };
}

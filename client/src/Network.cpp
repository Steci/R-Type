/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"
#include <map>
#include "../../engine/include/Engine.hpp"

client::Network::Network(std::string serverIP, int serverPort): _serverIP(serverIP), _serverPort(serverPort)
{
    if (fillSocket() == 84 || fillAddr() == 84 || bindSocket() == 84)
        throw std::invalid_argument("Error: Network creation failed");
}

client::Network::~Network()
{
}

int client::Network::fillSocket()
{
    int opt = 1;

    #ifdef linux
        _fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_fd == -1) {
            std::cerr << "Error: socket creation failed" << std::endl;
            return(84);
        }
        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
            std::cerr << "Error: socket options failed" << std::endl;
            return(84);
        }
    #endif

    #ifdef _WIN64
        WSADATA wsaData;
        int iResult;

        _fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (_fd == -1) {
            std::cerr << "Error: socket creation failed" << std::endl;
            return(84);
        }
        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
            std::cerr << "Error: socket options failed" << std::endl;
            return(84);
        }
        if (iResult != 0) {
            std::cerr << "Error: WSAStartup failed" << std::endl;
            return(84);
        }
    #endif
    return 0;
}

int client::Network::getRandomPort() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return std::rand() % 65536;
}

int client::Network::fillAddr()
{
    std::memset(&_addr, 0, sizeof(_addr));
    std::memset(&_serverAddr, 0, sizeof(_serverAddr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(getRandomPort());
    _serverAddr.sin_addr.s_addr = inet_addr(_serverIP.c_str());
    _serverAddr.sin_port = htons(_serverPort);
    std::cout << "Server IP: " << inet_ntoa(_serverAddr.sin_addr) << std::endl;
    std::cout << "Server port: " << ntohs(_serverAddr.sin_port) << std::endl;
    std::cout << "CLIENT port: " << ntohs(_addr.sin_port) << std::endl;
    return 0;
}

void client::Network::run()
{
    int server = 0;
    char buffer[1024];
    std::string serverMessage;
    std::map<int, std::string> commands = {{KEY_A, "A"}, {KEY_RIGHT, "RIGHT"}, {KEY_LEFT, "LEFT"}, {KEY_DOWN, "DOWN"}, {KEY_UP, "U"}, {KEY_ESCAPE, "ESCAPE"}};
    std::list<int> keys = {KEY_A, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_ESCAPE};
    SystemManager systemManager;
    int command;
    std::string connectionMessage = "connect " + _serverIP + " " + std::to_string(_serverPort);


    systemManager.addSystem<S_EventManager>();
    // systemManager.getSystem<S_EventManager>()->EventKeyPressed(keys);
    while(_isRunning) {
        command = systemManager.getSystem<S_EventManager>()->EventKeyPressed(keys);
        if (command != -1) {
            auto send = commands.find(command)->second;
            sendto(_fd, (void*)send, connectionMessage.length(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
        }
        std::memset(&buffer, 0, sizeof(buffer));
        server = recvfrom(_fd, (char *)buffer, 1024, MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        if (server == -1) {
            std::cerr << "Error: recvfrom failed" << std::endl;
            return;
        } else {
            buffer[server - 1] = '\0';
            if (handleCommands(buffer) == 84)
                std::cerr << "Unknow Command From Server..." << std::endl;
        }
    }
}

int client::Network::bindSocket()
{
    if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        std::cerr << "Error: socket binding failed" << std::endl;
        return(84);
    }
    return 0;
}

int client::Network::connectCommand()
{
    int server;
    char buffer[1024];
    auto startTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::seconds(5);
    std::string connectionMessage = "connect " + _serverIP + " " + std::to_string(_serverPort);

    sendto(_fd, connectionMessage.c_str(), connectionMessage.length(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
    while (std::chrono::high_resolution_clock::now() - startTime < duration) {
        std::memset(&buffer, 0, sizeof(buffer));
        server = recvfrom(_fd, (char *)buffer, 1024, MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        if (server != -1) {
            std::cout << "Successfully connected with the server." << std::endl;
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cerr << "Error: Connection timeout" << std::endl;
    return 84;
}

int client::Network::disconnectCommand()
{
    int bytesSent = sendto(_fd, "disconnect", 11, 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));

    if (bytesSent == -1)
        return 84;
    return 0;
}

int client::Network::inputCommand(std::string input)
{
    int bytesSent = 0;

    input = "input " + input;
    bytesSent = sendto(_fd, input.c_str(), input.length(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
    if (bytesSent == -1)
        return 84;
    return 0;
}

int client::Network::pingCommand()
{
    char buffer[1024];
    int bytesReturn = sendto(_fd, "ping", 5, 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));

    if (bytesReturn == -1)
        return 84;
    bytesReturn = recvfrom(_fd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
    // TODO: Check if it's really the ping response from the server.
    if (bytesReturn == -1) {
        return 84;
    }
    return 0;
}

int client::Network::handleCommands(const char *serverMessage)
{
    // TODO: Add all function they are supposed to receive: kill, kick, set_tickrate, update, and error.
    return (0);
}

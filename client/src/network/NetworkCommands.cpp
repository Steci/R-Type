/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** NetworkCommands
*/

#include "Network.hpp"

int client::Network::connectCommand()
{
    int server;
    std::vector<char> buffer;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::seconds(5);
    std::vector<char> connectionMessage = "connect " + _serverIP + " " + std::to_string(_serverPort);

    sendto(_fd, connectionMessage.data(), connectionMessage.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
    while (std::chrono::high_resolution_clock::now() - startTime < duration) {
        server = recvfrom(_fd, (std::vector<char>)buffer, 1024, MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        // TODO: Check for the size how to do it....
        if (server != -1) {
            std::cout << "Successfully connected with the server." << std::endl;
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cerr << "Error: Connection timeout" << std::endl;
    return 84;
}

int client::Network::disconnectCommand(std::vector<char> data)
{
    int bytesSent = sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&cli, sizeof(cli));

    if (bytesSent == -1)
        return 84;
    return 0;
}

int client::Network::inputCommand(std::vector<char> data)
{
    int bytesSent = 0;

    bytesSent = sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
    if (bytesSent == -1)
        return 84;
    return 0;
}

int client::Network::pingCommand(std::vector<char> data)
{
    std::vector<char> buffer;
    int bytesSent = sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&cli, sizeof(cli));

    if (bytesReturn == -1)
        return 84;
    bytesReturn = recvfrom(_fd, (std::vector<char>)buffer,1024, MSG_WAITALL, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
    // TODO: Check for the size how to do it....
    if (bytesReturn == -1) {
        return 84;
    }
    return 0;
}

std::string client::Network::handleCommands(const char *serverMessage)
{
    for (auto command : _commands)
        if (message == command) {
            return message;
        }
    std::cerr << "Wrong command" << std::endl;
    return "";
}

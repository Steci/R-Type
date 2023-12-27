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

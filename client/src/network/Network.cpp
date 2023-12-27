/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"

client::Network::Network(std::string serverIP, int serverPort): _serverIP(serverIP), _serverPort(serverPort)
{
    if (fillSocket() == 84 || fillAddr() == 84 || bindSocket() == 84)
        throw std::invalid_argument("Error: Network creation failed");
}

client::Network::~Network()
{
}

void client::Network::run()
{
    int server = 0;
    char buffer[1024];
    std::string serverMessage;

    while(_isRunning) {
        std::memset(&buffer, 0, sizeof(buffer));
        server = recvfrom(_fd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
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

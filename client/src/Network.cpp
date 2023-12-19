/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"

client::Network::Network(std::string serverIP, int port): _serverIP(serverIP), _port(port)
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
    _fd = socket(AF_INET, SOCK_STREAM, 0);

    if (_fd == -1) {
        std::cerr << "Error: socket creation failed" << std::endl;
        return(84);
    }
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        std::cerr << "Error: socket options failed" << std::endl;
        return(84);
    }
    return 0;
}

int client::Network::fillAddr()
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = INADDR_ANY;
    return 0;
}

void client::Network::run()
{
    int active = 0;

    FD_ZERO(&_readFds);
    FD_SET(_fd, &_readFds);
    while(_isRunning) {
        // TODO: Listen to server and do game stuff
    }
}

int client::Network::bindSocket()
{
    if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        std::cerr << "Error: socket binding failed" << std::endl;
        return(84);
    }
    if (listen(_fd, 1) == -1) {
        std::cerr << "Error: socket listening failed" << std::endl;
        return(84);
    }
    return 0;
}

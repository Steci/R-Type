/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"



server::Network::Network(int port, int maxClients): _port(port), _maxClients(maxClients)
{
    if (fillSocket() == 84 || fillAddr() == 84 || bindSocket() == 84)
        throw std::invalid_argument("Error: Network creation failed");
    setMaxFd();
}

server::Network::~Network()
{
}

int server::Network::fillSocket()
{
    int opt = 1;
    _fd = _maxClients;
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

int server::Network::fillAddr()
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = INADDR_ANY;
    return 0;
}

int server::Network::setMaxFd()
{
    FD_ZERO(&_readFds);
    FD_SET(_fd, &_readFds);
    _maxFd = _fd;
    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        FD_SET(client->getFd(), &_readFds);
        if (client->getFd() > _maxFd)
            _maxFd = client->getFd();
    }
    return 0;
}

void server::Network::run()
{
    int active;

    FD_ZERO(&_readFds);
    FD_SET(_fd, &_readFds);
    while(_isRunning) {
        setMaxFd();
        std::cout << "MaxFd + 1 = " << _maxFd + 1 << std::endl;
        active = select(_maxFd + 1, &_readFds, NULL, NULL, NULL); // il bloque mais il read pas les msg ;-;
        if (active == -1 && errno != EINTR) {
            std::cerr << "Error: select failed" << std::endl;
            return;
        }
        if (FD_ISSET(_fd, &_readFds))
            handleNewConnection();
        else
            handleClient();
    }
}

int server::Network::bindSocket()
{
    if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        std::cerr << "Error: socket binding failed" << std::endl;
        return(84);
    }
    if (listen(_fd, _maxClients) == -1) {
        std::cerr << "Error: socket listening failed" << std::endl;
        return(84);
    }
    return 0;
}

int server::Network::handleNewConnection()
{
    int newFd;
    struct sockaddr_in newAddr;
    socklen_t newAddrLen = sizeof(newAddr);
    std::string message = "";

    // std::cout << "New client trying to connect" << std::endl;
    // if (select(_fd + 1, &_readFds, NULL, NULL, NULL) == -1) {
    //     std::cerr << "Error: select failed" << std::endl;
    //     return(84);
    // }
    newFd = accept(_fd, (struct sockaddr *)&newAddr, &newAddrLen);
    if (newFd == -1) {
        std::cerr << "Error: socket accepting failed" << std::endl;
        return(84);
    }
    if (_clients.size() >= _maxClients) {
        std::cerr << "Error: new client tried to connect but server is full" << std::endl;
        message = "Server is full";
        send(newFd, message.c_str(), message.size(), 0);
        close(newFd);
        return 0;
    }
    _clients.push_back(Client(newFd, _clients.size(), "Player " + std::to_string(_clients.size())));
    std::cout << "New client connected: " << _clients.back().getName() << std::endl;
    dprintf(newFd, "Welcome aboard Captain");
    return 0;
}

int server::Network::handleClient() {
    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        if (FD_ISSET(client->getFd(), &_readFds)) {
            // if (client->checkClientCOnnected == -1) {
            //     std::cout << "Client disconnected: " << client->getName() << std::endl;
            //     FD_CLR(client->getFd(), &_readFds);
            //     _clients.erase(client);
            //     return 0;
            // }
            std::cout << "Protocol 3: Protect the pilot " << client->getName() << std::endl;
            client->readClient();
        }
    }
    return 0;
}
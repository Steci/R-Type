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
    int active = 0;

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
    dprintf(newFd, "Welcome aboard Captain\n");
    return 0;
}

int server::Network::handleClient() {
    std::vector<Client> disconnectedClients;

    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        if (FD_ISSET(client->getFd(), &_readFds)) {
            // if (client->checkClientCOnnected == -1) {
            //     std::cout << "Client disconnected: " << client->getName() << std::endl;
            //     FD_CLR(client->getFd(), &_readFds);
            //     _clients.erase(client);
            //     return 0;
            // }
            if (client->readClient() == -1) {
                disconnectedClients.push_back(*client);
                FD_CLR(client->getFd(), &_readFds);
            }
        }
    }
    for (auto client = disconnectedClients.begin(); client != disconnectedClients.end(); client++) {
        _clients.erase(std::find(_clients.begin(), _clients.end(), *client));
    }
    return 0; //set_tickrate
}

int server::Network::commandKill() const
{
    std::string kickMessage = "You've been kicked: Server Disconnection";
    int fd = 0;

    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        fd = client->getFd();
        send(fd, kickMessage.c_str(), kickMessage.size(), 0);
        // TODO: Error handling if it didn't send
        _clients.erase(client);
        close(_fd);
    }
    close(this->_fd);
    return 0;
}

int server::Network::commandKick(int _fd, std::string message) const
{
    std::string kickMessage = "You've been kicked: " + message;

    send(_fd, kickMessage.c_str(), kickMessage.size(), 0);
    // TODO: Error handling if it didn't send
    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        (client->getFd() == _fd) {
            close(_fd);
            _clients.erase(client);
           return 0;
            // Return success
        }
    }
    return 1;
    // Return client not found
}

int server::Network::commandSetTickrate(int _fd) const
{
    std::string newTickrate = "New tickrate: " + std::to_string(0);

    send(_fd, newTickrate.c_str(), newTickrate.size(), 0);
    // TODO: Error handling if it didn't send
}

int server::Network::commandPing(int _fd) const
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::string pingRes = std::to_string(duration.count());

    send(_fd, pingRes.c_str(), pingRes.size(), 0);
    // TODO: Error handling if it didn't send
}

int server::Network::commandError(int _fd, std::string error) const
{
    std::string errorMessage = "Error: " + error;

    send(_fd, errorMessage.c_str(), errorMessage.size(), 0);
    // TODO: Error handling if it didn't send
}

// server::Network &server::Network::operator=(const server::Network &other)
// {
//     _port = other._port;
//     _maxClients = other._maxClients;
//     _isRunning = other._isRunning;
//     _fd = other._fd;
//     _maxFd = other._maxFd;
//     _readFds = other._readFds;
//     _addr = other._addr;
//     _clients = other._clients;
//     return *this;
// }
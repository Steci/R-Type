/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"

server::Network::Network(int port, int maxClients): _port(port != 0 ? port : 9001), _maxClients(maxClients != 0 ? maxClients : 4)
{
    if (fillSocket() == 84 || fillAddr() == 84 || bindSocket() == 84)
        throw std::invalid_argument("Error: Network creation failed");
    std::cout << "Network created on port " << _port << " with " << _maxClients << " max clients" << std::endl;
}

server::Network::~Network()
{
}

int server::Network::fillSocket()
{
    int opt = 1;

    _fd = _maxClients;

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

int server::Network::fillAddr()
{
    std::memset(&_addr, 0, sizeof(_addr));
    std::memset(&_clientAddr, 0, sizeof(_clientAddr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = INADDR_ANY;
    return 0;
}

void server::Network::run()
{
    int client;
    char buffer[1024];

    while(_isRunning) {
        buffer[0] = '\0';
        client = recvfrom(_fd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&_clientAddr, &_clientAddrLen);
        if (client == -1) {
            std::cerr << "Error: recvfrom failed" << std::endl;
            return;
        }
        if (handleClient() != 84) {
        std::cout << "Client message: " << buffer << std::endl;
        }
    }
}

int server::Network::bindSocket()
{
    if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        std::cerr << "Error: socket binding failed" << std::endl;
        return(84);
    }
    return 0;
}

int server::Network::handleNewConnection()
{
    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        if (inet_ntoa(client->getAddr().sin_addr) == inet_ntoa(_clientAddr.sin_addr) && client->getAddr().sin_port == _clientAddr.sin_port) {
            std::cout << "Client already connected" << std::endl;
            return 0;
        }
    }
    _clients.push_back(Client(_clientAddr, _clients.size() + 1, "Player " + std::to_string(_clients.size() + 1)));
    std::cout << "New client connected" << std::endl;
    return 0;
}

int server::Network::handleClient() {
    std::vector<Client> disconnectedClients;

    if (_clientAddr.sin_addr.s_addr == INADDR_ANY) {
        std::cerr << "Error: ip or port recuperation failed" << std::endl;
        return 84;
    }
    std::cout << "Client IP: " << inet_ntoa(_clientAddr.sin_addr) << std::endl;
    std::cout << "Client port: " << ntohs(_clientAddr.sin_port) << std::endl;
    if (handleNewConnection() == 84)
        return 84;
    return 0;
}

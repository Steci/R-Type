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
    std::cout << "Server IP: " << inet_ntoa(_addr.sin_addr) << std::endl;
    std::cout << "Server port: " << ntohs(_addr.sin_port) << std::endl;
    std::cout << "Server port: " << _addr.sin_port << std::endl;
    return 0;
}

void server::Network::run(Game *game)
{
    int client;
    //char buffer[1024];
    int id;
    std::string message;
    std::vector<char> buffer(1024);
    server::Serialize convert;

    while(_isRunning) {
        client = recvfrom(_fd, buffer.data(), buffer.size(), MSG_DONTWAIT, (struct sockaddr *)&_clientAddr, &_clientAddrLen);
        if (client < 0) {
            continue;
        }
        std::string resData = convert.deserialize(buffer);
        id = handleClient(resData);
        if (id != 84) {
            if (resData == "TICKRATE") {
                std::vector<char> data = game->serialize();
                commandSetTickrate(convert.deserialize(data));
            } else
                manageMessage(resData, id, game);
        }
        updateClients(id, resData, game);
    }
}

void server::Network::updateClients(int client_id, std::string message, Game *game)
{
    std::vector<std::string> functions_clients;

    functions_clients = (*game).getFunctionsClient();
    for (auto function : functions_clients) {
        for (auto client = _clients.begin(); client != _clients.end(); client++) {
            struct sockaddr_in cli = client->getAddr();
            sendto(_fd, function.c_str(), function.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
        }
    }
}

void server::Network::manageMessage(std::string message, int client_id, Game *game)
{
    std::string messageParse = handleClientMessage(message, client_id);
    if (std::strcmp(message.c_str(), messageParse.c_str()) != 0)
        (*game).addFunction(messageParse);
    std::cout << "Client message: " << message << " end " << std::endl;
}

std::string server::Network::handleClientMessage(std::string message, int client_id)
{
    for (auto command : _commands) {
        if (message == command) {
            message = message + " " + std::to_string(client_id);
            return message;
        } else if (message.rfind(command, 0) == 0 && command == "UPDATE") {
            message = message + " " + std::to_string(client_id);
            return message;
        }
    }
    std::cout << "Wrong command" << std::endl;
    return message;
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
            // std::cout << "Client already connected" << std::endl;
            return client->getId();
        }
    }
    _clients.push_back(Client(_clientAddr, _clients.size(), "Player " + std::to_string(_clients.size() + 1)));
    sockaddr_in cli = _clients.back().getAddr();
    server::Serialize convert;
    std::vector<char> dataTest = convert.serialize(std::to_string(_clients.size() + 1));
    sendto(_fd, dataTest.data(), dataTest.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
    // ssize_t bytesSent = sendto(_fd, "Welcome to the server", 22, 0, (struct sockaddr *)&cli, sizeof(cli));
    // if (bytesSent == -1)
    //     return 84;
    std::cout << "New client connected" << std::endl;
    return 0;
}

int server::Network::handleClient(std::string message) {
    std::vector<Client> disconnectedClients;

    if (_clientAddr.sin_addr.s_addr == INADDR_ANY) {
        std::cerr << "Error: ip or port recuperation failed" << std::endl;
        return 84;
    }
    std::cout << "Client IP: " << inet_ntoa(_clientAddr.sin_addr) << std::endl;
    // std::cout << "Client port: " << ntohs(_clientAddr.sin_port) << std::endl;
    return handleNewConnection();
}


int server::Network::commandKill(std::string data)
{
    server::Serialize convert;
    std::vector<char> dataTest = convert.serialize(data);

    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        struct sockaddr_in cli = client->getAddr();
        sendto(_fd, dataTest.data(), dataTest.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
        // TODO: Error handling if it didn't send
    }
    _clients.clear();
    return 0;
}

int server::Network::commandKick(std::string data, int client_id)
{
    server::Serialize convert;
    std::vector<char> dataTest = convert.serialize(data);

    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        if (client->getId() == client_id) {
            struct sockaddr_in cli = client->getAddr();
            sendto(_fd, dataTest.data(), dataTest.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
            _clients.erase(client);
           return 0;
        }
    }
    return 1;
}

int server::Network::commandSetTickrate(std::string data) const
{
    server::Serialize convert;
    std::vector<char> dataTest = convert.serialize(data);

    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        struct sockaddr_in cli = client->getAddr();
        sendto(_fd, dataTest.data(), dataTest.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
    }
    return 0;
}

int server::Network::commandPing(std::string data, int client_id) const
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::string pingRes = std::to_string(duration.count());

    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        if (client->getId() == client_id) {
            struct sockaddr_in cli = client->getAddr();
            sendto(_fd, pingRes.c_str(), pingRes.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
           return 0;
            // Return success
        }
    }
    // TODO: Error handling if it didn't send
    return 0;
}

int server::Network::commandError(std::string data, int client_id) const
{
    server::Serialize convert;
    std::vector<char> dataTest = convert.serialize(data);

    for (auto client = _clients.begin(); client != _clients.end(); client++)
        if (client->getId() == client_id) {
            struct sockaddr_in cli = client->getAddr();
            sendto(_fd, dataTest.data(), dataTest.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
        }
    return 0;
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

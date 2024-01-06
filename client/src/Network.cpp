/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"

client::Network::Network(std::string serverIP, int serverPort): _serverIP(serverIP), _serverPort(serverPort), _isRunning(true)
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
        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
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

void client::Network::run(Game *game)
{
    int server = 0;
    std::vector<char> buffer(1024);
    client::Serialize convert;

    while(_isRunning) {
        server = recvfrom(_fd, buffer.data(), buffer.size(), MSG_WAITALL, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        checkInteraction(game);
        if (server == -1) {
            std::cerr << "Error: recvfrom failed" << std::endl;
            return;
        } else {
            handleCommands(buffer, game);
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
    auto startTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::seconds(5);
    client::Connection connect;
    client::Connection receiveConnection;
    std::vector<char> data = connect.serializeConnection();
    std::vector<char> receiveData(sizeof(client::Connection));

    while (std::chrono::high_resolution_clock::now() - startTime < duration) {
        sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
        server = recvfrom(_fd, receiveData.data(), receiveData.size(), MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        if (server != -1) {
            std::cout << "Info received" << std::endl;
            receiveConnection.deserializeConnection(receiveData);
            if (receiveConnection.getConnected() == 1) {
                std::cout << "Successfully connected with the server." << std::endl;
                return 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cerr << "Error: Connection timeout" << std::endl;
    return 84;
}

std::string client::Network::inputHandle(std::string message)
{
    for (auto input : _inputs) {
        if (message == input) {
            return "UPDATE " + message;
        }
    }
    std::cerr << "Wrong input" << std::endl;
    return "";
}

int client::Network::inputCommand(std::string input)
{
    client::Serialize convert;
    std::vector<char> dataTest = convert.serialize(input);
    int bytesSent = sendto(_fd, dataTest.data(), dataTest.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));

    if (bytesSent == -1)
        return 84;
    return 0;
}

void client::Network::handleCommands(std::vector<char> buffer, Game *game)
{
    client::Frame frame;

    // std::cout << "frame received" << std::endl;
    frame.deserializeFrame(buffer);
    // std::cout << "frame deserialized" << std::endl;
    if (frame.getTick() != -1) {
        game->addFrame(frame);
        return;
    }
}

void client::Network::checkInteraction(Game *game)
{
    std::vector<Interaction> interactions = game->getInteractions();
    std::vector<char> data;

    if (interactions.size() > 0) {
        data = interactions[0].serializeInteraction();
        sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
        game->deleteInteraction(0);
    }
}
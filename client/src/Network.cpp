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
    #ifdef __linux__
        close(_fd);
    #endif
    #ifdef _WIN64
        closesocket(_fd);
        WSACleanup();
    #endif
}

int client::Network::fillSocket()
{
    int opt = 1;

    #ifdef __linux__
        _fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_fd == -1) {
            std::cerr << "Error: socket creation failed" << std::endl;
            return(84);
        }
        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
            std::cerr << "Error: socket options failed" << std::endl;
            close(_fd);
            return (84);
        }
    #endif

    #ifdef _WIN64
        int iResult = 0;

        iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
        if (iResult != NO_ERROR) {
            std::cerr << "Error: WSAStartup failed" << std::endl;
            return (84);
        }
        _fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_fd == INVALID_SOCKET) {
            std::cerr << "Error: socket creation failed" << WSAGetLastError() << std::endl;
            closesocket(_fd);
            WSACleanup();
            return (84);
        }
        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&opt), sizeof(int)) == -1) {
            std::cerr << "Error: socket options failed" << WSAGetLastError() << std::endl;
            return (84);
        }

        unsigned read_timeout_ms = 10;
        setsockopt(_fd, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&read_timeout_ms), sizeof(read_timeout_ms));
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
    _addr.sin_port = htons(getRandomPort());
    _addr.sin_addr.s_addr = INADDR_ANY;
    _serverAddr.sin_addr.s_addr = inet_addr(_serverIP.c_str());
    _serverAddr.sin_port = htons(_serverPort);
    _serverAddr.sin_family = AF_INET;
    #ifdef _WIN64
        _serverAddrLen = sizeof(_serverAddr);
    #endif
    std::cout << "Server IP: " << inet_ntoa(_serverAddr.sin_addr) << std::endl;
    std::cout << "Server port: " << ntohs(_serverAddr.sin_port) << std::endl;
    std::cout << "Client port: " << ntohs(_addr.sin_port) << std::endl;
    return 0;
}

void client::Network::run(Game *game)
{
    int server = 0;
    std::vector<char> buffer(1024);
    client::Serialize convert;
    std::vector<Game> games;

    std::cerr << "CLIENT RUNNING :D" << std::endl;
    while(_isRunning) {
        #ifdef __linux__
            server = recvfrom(_fd, buffer.data(), buffer.size(), MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
            if (server == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue;
                } else {
                    std::cerr << "Error: recvfrom failed - " << strerror(errno) << std::endl;
                    return;
                }
            }
        #endif
        #ifdef _WIN64
            // si probleme de non bloquant ca peut etre le MSG_PEEK ! Si c'est ca changer en autre chose
            server = recvfrom(_fd, buffer.data(), buffer.size(), MSG_PEEK, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        #endif
        checkInteraction(game);
        if (server == -1) {
            std::cerr << "Error: recvfrom failed - " << strerror(errno) << std::endl;
            return;
        } else {
            handleCommands(buffer, game);
        }
    }
}

int client::Network::bindSocket()
{
    #ifdef __linux__
        if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
            std::cerr << "Error: socket binding failed" << std::endl;
            return(84);
        }
        return 0;
    #endif
    #ifdef _WIN64
        if (bind(_fd, (SOCKADDR *)&_addr, sizeof(_addr)) == -1) {
            std::cerr << "Error: socket binding failed" << std::endl;
            return(84);
        }
        return 0;
    #endif
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
    int res = 0;

    while (std::chrono::high_resolution_clock::now() - startTime < duration) {
        res = sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
        if (res == -1) {
            std::cerr << "Connection failure..." << std::endl;
        }
        #ifdef __linux__
            server = recvfrom(_fd, receiveData.data(), receiveData.size(), MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        #endif
        #ifdef _WIN64
            server = recvfrom(_fd, receiveData.data(), receiveData.size(), MSG_PEEK, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
            if (server == SOCKET_ERROR) {
                std::cerr << "Empty... error: " << WSAGetLastError() << std::endl;
            }
        #endif
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
        game->deleteInteraction(1);
    }
}

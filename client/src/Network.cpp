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
        _fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
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
    _serverAddrLen = sizeof(_serverAddr);
    std::cout << "Server IP: " << inet_ntoa(_serverAddr.sin_addr) << std::endl;
    std::cout << "Server port: " << ntohs(_serverAddr.sin_port) << std::endl;
    std::cout << "Client port: " << ntohs(_addr.sin_port) << std::endl;
    return 0;
}

void client::Network::run(Game *game)
{
    int server = 0;
    std::vector<char> buffer(4096);
    client::Serialize convert;
    std::vector<Game> games;

    while((*game).getMenu()->getStatusMenu() && (*game).getStatusGame() != true) {
        if ((*game).getMenu()->getCreateGame() && connectCommand(game, 1) == 0) {
            (*game).getMenu()->setStatusMenu(false);
        } else if ((*game).getMenu()->getCreateGame()) {
            (*game).getMenu()->setError("Error: Connection failed");
            (*game).getMenu()->setCreateGame(false);
        } else if ((*game).getMenu()->getJoinGame() && connectCommand(game, 0, 1, (*game).getMenu()->getIdServerJoin()) == 0) {
            (*game).getMenu()->setStatusMenu(false);
        } else if ((*game).getMenu()->getJoinGame()) {
            (*game).getMenu()->setError("Error: Connection failed");
            (*game).getMenu()->setJoinGame(false);
        }
    }
    while (_isRunning && (*game).getStatusGame() != true) {
        #ifdef __linux__
            server = recvfrom(_fd, buffer.data(), buffer.size(), MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        #endif
        #ifdef _WIN64
            server = recvfrom(_fd, buffer.data(), buffer.size(), 0, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
        #endif
        checkInteraction(game);
        handleCommands(buffer, game);
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

int client::Network::connectCommand(Game *game, int createGame, int joinGame, int gameId)
{
    int server;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::seconds(5);
    client::Connection connect;
    client::Connection receiveConnection;
    connect.setCreateGame(createGame);
    connect.setJoinGame(joinGame);
    connect.setGameId(gameId);
    std::vector<char> data = connect.serializeConnection();
    std::vector<char> receiveData(1024);
    int res = 0;

    // while (std::chrono::high_resolution_clock::now() - startTime < duration) {
    //     server = recvfrom(_fd, receiveData.data(), receiveData.size(), MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
    // }
    // startTime = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::seconds(5);
    while (std::chrono::high_resolution_clock::now() - startTime < duration) {
        res = sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
        if (res == -1) {
            std::cerr << "Connection failure..." << std::endl;
        }
        #ifdef __linux__
            server = recvfrom(_fd, receiveData.data(), receiveData.size(), MSG_DONTWAIT, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
            if (server == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue;
                } else {
                    std::cerr << "Error: recvfrom failed - " << strerror(errno) << std::endl;
                }
            }
        #endif
        #ifdef _WIN64
            server = recvfrom(_fd, receiveData.data(), receiveData.size(), 0, (struct sockaddr *)&_serverAddr, &_serverAddrLen);
            if (server == SOCKET_ERROR ) {
                std::cerr << "Error: recvfrom failed - " << WSAGetLastError() << std::endl;
            }
        #endif
        if (server != -1) {
            receiveConnection.deserializeConnection(receiveData);
            // printf("receive connected = %d, join game = %d\n", receiveConnection.getConnected(), receiveConnection.getJoinGame());
            if (receiveConnection.getConnected() == 1 && receiveConnection.getJoinGame() == -1) {
                std::cout << "Successfully connected with the server." << std::endl;
                return 0;
            } else if (receiveConnection.getJoinGame() == 2) {
                printf("get info\n");
                (*game).getMenu()->setIdGames(receiveConnection.getGameIds());
                return 1;
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
    int res = 0;

    if (interactions.size() > 0) {
        data = interactions[0].serializeInteraction();
        res = sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr));
        if (res == -1) {
            std::cerr << "Sendto Interaction failure..." << std::endl;
        }
        game->deleteInteraction(1);
    }
}

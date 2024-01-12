/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Network.cpp
*/

#include "Network.hpp"
#include "Entity.hpp"
#include "Component.hpp"

client::Network::Network(std::string serverIP, int serverPort): _serverIP(serverIP), _serverPort(serverPort)
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
    SparseArray<IEntity> new_entities;
    SparseArray<IEntity> entities;
    client::Frame frame;
    // TODO parse entity buffer
    /*
    
    for (auto charact : buffer) {
        std::cout << charact;
    }
    std::cout << std::endl;
    */










    int tick = 0;
    auto it = buffer.begin();
    E_Player player(0, 0, 0, 0);
    E_Enemy enemy(0, 0, 0, 0, 0);
    E_Bullet bullet(0, 0, 0, 0, 0, 0, 0, 0);


     std::cout << "tick : " << tick << std::endl;
    if (std::distance(it, buffer.end()) >= sizeof(tick)) {
        std::memcpy(&tick, &it, sizeof(tick));
        it += sizeof(tick);
    }
    std::cout << "tick : " << tick << std::endl;



    while (it < buffer.end() && !frame.isEndMarker(it, buffer)) {
        std::string entityType;
        while (it != buffer.end() && *it != '\0') {
            entityType.push_back(*it);
            ++it;
        }
        ++it;
        if (entityType == "E_Player") {
            size_t size_player = sizeof(C_Transform) + sizeof(C_Health) + sizeof(C_Hitbox) + sizeof(C_Score);
            player.deserializeFromVector(std::vector<char>(it, it + size_player));
            it += sizeof(size_player);
            C_Transform *transform = Engine::getComponentRef<C_Transform>(player);
            C_Health *health = Engine::getComponentRef<C_Health>(player);
            C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(player);
            C_Score *score = Engine::getComponentRef<C_Score>(player);
            auto playerShared = std::make_shared<E_Player>(player);
            new_entities.add(playerShared);
            //std::cout << ">>>>>>>>>>>>>>>>>>>>>player added" << std::endl;
        } else if (entityType == "E_Enemy") {
            size_t size_enemy = sizeof(C_Transform) + sizeof(C_Health) + sizeof(C_Hitbox) + sizeof(C_EnemyInfo);
            enemy.deserializeFromVector(std::vector<char>(it, it + size_enemy));
            it += sizeof(size_enemy);
            C_Transform *transform = Engine::getComponentRef<C_Transform>(enemy);
            C_Health *health = Engine::getComponentRef<C_Health>(enemy);
            C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(enemy);
            C_EnemyInfo *ennemyInfo = Engine::getComponentRef<C_EnemyInfo>(enemy);
            auto enemyShared = std::make_shared<E_Enemy>(transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y, ennemyInfo->_type);
            new_entities.add(enemyShared);
            //std::cout << ">>>>>>>>>>>>>>>>>>>>>enemy added" << std::endl;
        } else if (entityType == "E_Bullet") {
            // size_t size_bullet = sizeof(C_Transform) + sizeof(C_Damage) + sizeof(C_Hitbox) + sizeof(int);
            size_t size_bullet = sizeof(C_Transform) + sizeof(C_Damage) + sizeof(int);
            bullet.deserializeFromVector(std::vector<char>(it, it + sizeof(bullet)));
            it += sizeof(bullet);
            auto bulletShared = std::make_shared<E_Bullet>(bullet);
            new_entities.add(bulletShared);
            //std::cout << ">>>>>>>>>>>>>>>>>>>>>bullet added" << std::endl;
        }
        if (frame.isEndMarker(it, buffer)) {
            break;
        }
    }













    // std::cout << "frame received" << std::endl;
    // frame.deserializeFrame(buffer);
    // std::cout << "frame deserialized" << std::endl;
    std::cout << "TICK ======= " << tick << std::endl;
    if (frame.getTick() == -1)
        return;
    int ii = 0;
    for (auto fram : game->getFrames()) {
        std::cout << ">>>>>>>>>>>>>>>>>>>>>frame nb" << ii << std::endl;
        ii += 1;
        if (fram.getTick() == tick) {
            /*
            entities = fram.getEntities();
            for (auto entity : new_entities) {
                entities.add(entity)
            }
            frame.setArray(new_entities);
            */
            std::cout << ">>>>>>>>>>>>>>>>>>>>>frame already received" <<tick << std::endl;
            //TODO add entities to the frame
            return;
        }
    }
    //TODO add frame to the game
    std::cout << ">>>>>>>>>>>>>>>>>>>>>frame added" << std::endl;
    frame.setTick(tick);
    frame.setArray(new_entities);
    game->addFrame(frame);
    return;
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
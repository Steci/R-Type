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

// void server::Network::run(Game *game)
void server::Network::run()
{
    int client;
    //char buffer[1024];
    int id;
    Connection connect;
    Interaction interaction;
    std::string message;
    std::vector<char> buffer(1024);
    std::vector<std::unique_ptr<Game>> games;
    std::vector<int> idNotUsableGame;
    std::map<int, std::thread> threads;

    while(_isRunning) {
        client = 0;
        client = recvfrom(_fd, buffer.data(), buffer.size(), MSG_DONTWAIT, (struct sockaddr *)&_clientAddr, &_clientAddrLen);
        for (int i = 0; i < games.size(); ++i) {
            // printf("game id = %d\n", games[i]->getGameId());
            updateClients(&games[i]);
        }
        // updateClients(game);
        if (client < 0) {
            continue;
        }
        // std::string resData = convert.deserialize(buffer);
        auto[id, connect] = handleClient(buffer);
        if (id != -1) {
            for (auto game = games.begin(); game != games.end(); game++) {
                interaction = manageClient(buffer, id, game->get());
            }
            if (connect.getCreateGame() == 1) {
                for (auto client = _clients.begin(); client != _clients.end(); client++) {
                    if (client->getId() == connect.getId() && client->getGameId() == -1) {
                        printf("create game\n");
                        auto gameTmp = std::make_unique<Game>();
                        gameTmp->setGameId(CreateGame(idNotUsableGame));
                        idNotUsableGame.push_back(gameTmp->getGameId());
                        threads[gameTmp->getGameId()] = std::thread(&Game::run, gameTmp.get());
                        gameTmp->addInteraction(interaction);
                        client->setGameId(gameTmp->getGameId());
                        connect.setJoinGame(gameTmp->getGameId());
                        games.push_back(std::move(gameTmp));
                        break;
                    }
                }
            }
            if (id == 0) {
                interaction.setClientID(connect.getId());
                interaction.setConnect(1);
                for(auto game = games.begin(); game != games.end(); game++) {
                    if (game->get()->getGameId() == connect.getJoinGame()) {
                        game->get()->addInteraction(interaction);
                    }
                }
            }
        }
        // } else if (id == 0) {
        //     // (*game).addInteraction(interaction);
        // }
    }
}

int server::Network::CreateGame(std::vector<int> idNotUsableGame)
{
    int id = 0;

    for (int i = 0; i < _maxClients; i++) {
        if (std::find(idNotUsableGame.begin(), idNotUsableGame.end(), i) == idNotUsableGame.end()) {
            id = i;
            break;
        }
    }
    return id;
}

server::Interaction server::Network::manageClient(std::vector<char> buffer, int client_id, Game *game)
{
    Interaction interaction;

    interaction.deserializeInteraction(buffer);
    interaction.setClientID(client_id);
    // std::cout << "Interaction: " << interaction.getMovement() << std::endl;
    if (interaction.getMovement() != -1 && interaction.getCreateGame() != 1)
        (*game).addInteraction(interaction);
    return interaction;
}

void server::Network::updateClients(std::unique_ptr<Game> *game)
{
    std::vector<std::string> functions_clients;
    std::vector<Frame> frames = (*game)->getFrames();
    Frame frame;
    bool frame_found = false;
    int last_tick_send = (*game)->getLastTickSend();

    if (frames.size() == 0 || frames.size() <= last_tick_send + 1) {
        return;
    }
    for (auto frame_tmp : frames) {
        if (frame_tmp.getTick() == last_tick_send + 1 || frame_tmp.getTick() > last_tick_send + 1) {
            frame = frame_tmp;
            frame_found = true;
            break;
        }
    }
    if (!frame_found) {
        return;
    }
    (*game)->setLastTickSend(frame.getTick());
    std::vector<char> data = frame.serializeFrame();
    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        // printf("client game id = %d, game id = %d, with id %d\n", client->getGameId(), (*game)->getGameId(), client->getId());
        if (client->getGameId() == (*game)->getGameId()) {
            // printf("send frame from game %d to client %d\n", (*game)->getGameId(), client->getId());
            struct sockaddr_in cli = client->getAddr();
            sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
        }
    }
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

std::tuple<int, server::Connection> server::Network::handleNewConnection(Connection connect)
{
    for (auto client = _clients.begin(); client != _clients.end(); client++) {
        if (inet_ntoa(client->getAddr().sin_addr) == inet_ntoa(_clientAddr.sin_addr) && client->getAddr().sin_port == _clientAddr.sin_port) {
            // std::cout << "Client already connected" << std::endl;
            return std::make_tuple(client->getId(), connect);
        }
    }
    connect.setId(_clients.size() + 1);
    printf("Id Client = %d\n", _clients.size() + 1);
    _clients.push_back(Client(_clientAddr, _clients.size() + 1, "Player " + std::to_string(_clients.size() + 1)));
    sockaddr_in cli = _clients.back().getAddr();
    connect.setConnected(1);
    std::vector<char> data = connect.serializeConnection();
    sendto(_fd, data.data(), data.size(), 0, (struct sockaddr *)&cli, sizeof(cli));
    // ssize_t bytesSent = sendto(_fd, "Welcome to the server", 22, 0, (struct sockaddr *)&cli, sizeof(cli));
    // if (bytesSent == -1)
    //     return 84;
    std::cout << "New client connected" << std::endl;
    return std::make_tuple(0, connect);
}

std::tuple<int, server::Connection> server::Network::handleClient(std::vector<char> buffer) {
    Connection connect;

    if (_clientAddr.sin_addr.s_addr == INADDR_ANY) {
        std::cerr << "Error: ip or port recuperation failed" << std::endl;
        return std::make_tuple(-1, connect);
    }
    // std::cout << "Client IP: " << inet_ntoa(_clientAddr.sin_addr) << std::endl;
    // std::cout << "Client port: " << ntohs(_clientAddr.sin_port) << std::endl;
    connect.deserializeConnection(buffer);
    return handleNewConnection(connect);
    // std::vector<Client> disconnectedClients;

    // return handleNewConnection();
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

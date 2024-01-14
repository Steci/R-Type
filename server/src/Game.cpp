/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "Game.hpp"

server::Game::Game()
{
    _tick = 0;
}

bool findPlayerID(std::vector<std::pair<IEntity *, int>> playerList, int playerIndex)
{
    if (playerList.size() == 0)
        return false;
    for (auto pair : playerList) {
        if (pair.second == playerIndex)
            return true;
    }
    return false;
}

void server::Game::run()
{
    printf("Game started\n");
    srand(time(NULL));

    SystemManager manager;
    SparseArray<IEntity> entities;
    std::vector<Interaction> interaction_client;

    manager.addSystem<S_Collision>(entities);
    manager.addSystem<S_EnemyAI>(entities);
    manager.addSystem<S_Spawner>(entities);
    manager.addSystem<S_Weapon>(entities, _tick);

    int numClientID = 0;
    bool startGame = false;
    int firingSpeed = manager.getSystem<S_Weapon>()->getFiringSpeed();

    while (true) {
        _mutex.lock();
        if (_interaction_client.size() > 0) {
            interaction_client = _interaction_client;
            _interaction_client.clear();
        }
        _mutex.unlock();
        if (interaction_client.size() > 0) {
            for (auto interaction : interaction_client) {
                for (auto entity : entities.getAll()) {
                    if (entity->getType() == "E_Player" && interaction.getClientID() == entity->getIdServer()) {
                        interaction.setClientID(entity->getId());
                        break;
                    }
                }
                if (interaction.getConnect() == 1) {
                    printf("New Player with ID : %d\n", interaction.getClientID());
                    std::shared_ptr<E_Player> player = std::make_shared<E_Player>(50, 50, 33.2, 17.2);
                    player->setId(getAvailaibleId());
                    player->setIdServer(interaction.getClientID());
                    entities.add(player, player.get()->getId());
                    setAvailaibleId(player->getId() + 1);
                    startGame = true;
                    interaction.setMovement(0);
                }
                if (interaction.getQuit() == 1) {
                    printf("Player with ID : %d quit\n", interaction.getClientID());
                    entities.remove(interaction.getClientID());
                    interaction.setMovement(0);
                }
                if (interaction.getShoot() == 1 && startGame == true){
                    // shoot
                    C_Transform *transform = Engine::getComponentRef<C_Transform>(entities.get(interaction.getClientID()));
                    if (transform == nullptr)
                        continue;
                    manager.getSystem<S_Weapon>()->shootPlayer(interaction.getClientID());
                }
                if (interaction.getMovement() == 1 && startGame == true){
                    // go up
                    C_Transform *transform = Engine::getComponentRef<C_Transform>(entities.get(interaction.getClientID()));
                    if (transform == nullptr)
                        continue;
                    transform->_position.y -= (8 * TICK_SPEED) / DESIRED_SPEED;
                }
                if (interaction.getMovement() == 2 && startGame == true){
                    // go right
                    C_Transform *transform = Engine::getComponentRef<C_Transform>(entities.get(interaction.getClientID()));
                    if (transform == nullptr)
                        continue;
                    transform->_position.x += (8 * TICK_SPEED) / DESIRED_SPEED;
                }
                if (interaction.getMovement() == 3 && startGame == true){
                    // go down
                    C_Transform *transform = Engine::getComponentRef<C_Transform>(entities.get(interaction.getClientID()));
                    if (transform == nullptr)
                        continue;
                    transform->_position.y += (8 * TICK_SPEED) / DESIRED_SPEED;
                }
                if (interaction.getMovement() == 4 && startGame == true){
                    // go left
                    C_Transform *transform = Engine::getComponentRef<C_Transform>(entities.get(interaction.getClientID()));
                    if (transform == nullptr)
                        continue;
                    transform->_position.x -= (8 * TICK_SPEED) / DESIRED_SPEED;
                }
            }
        }

        _functions.clear();
        manager.update();
        _tick++;

        fillFrame(entities);
        interaction_client.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(_tickSpeed));
    }
}

void server::Game::fillFrame(SparseArray<IEntity> entities)
{
    //remplir la frame ici
    Frame frame;

    frame.setArray(entities);
    frame.setGameId(_gameId);
    frame.setTick(_tick);
    _mutex_frame.lock();
    _frames.push_back(frame);
    _mutex_frame.unlock();
}

std::vector<std::string> server::Game::getFunctionsClient()
{
    _mutex_client.lock();
    std::vector<std::string> functions = _functions_client;
    _functions_client.clear();
    _mutex_client.unlock();
    return functions;
}

std::vector<char> server::Frame::serializeFrame()
{
    std::vector<char> data;
    data.insert(data.end(), reinterpret_cast<const char*>(&_tick), reinterpret_cast<const char*>(&_tick) + sizeof(_tick));
    data.insert(data.end(), reinterpret_cast<const char*>(&_gameId), reinterpret_cast<const char*>(&_gameId) + sizeof(_gameId));

    auto playerData = _entities.serializeToVector("E_Player");
    data.insert(data.end(), playerData.begin(), playerData.end());

    auto enemyData = _entities.serializeToVector("E_Enemy");
    data.insert(data.end(), enemyData.begin(), enemyData.end());

    auto bulletData = _entities.serializeToVector("E_Bullet");
    data.insert(data.end(), bulletData.begin(), bulletData.end());
    // if (data.size() > 4)
    //     printf("\n");

    std::string endMarker = "END";
    data.insert(data.end(), endMarker.begin(), endMarker.end());
    data.push_back('\0');

    return data;
}

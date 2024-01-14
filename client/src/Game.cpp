/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "Game.hpp"
#ifdef _WIN64
    #define NOGDI
    #define NOUSER
    #define MMNOSOUND
    #include <winsock2.h>
#endif

namespace client {
    void Game::createTextures()
    {
        _ennemy_sprites[1] = Infos(65.25, 132, "./assets/r-enemy-1.png");
        _ennemy_sprites[2] = Infos(33.25, 36, "./assets/r-enemy-2.png");
        _ennemy_sprites[3] = Infos(65.2, 66, "./assets/r-enemy-3.png");
        _player_sprites[0] = Infos(33.2, 18, "./assets/r-player-1.png");
        _player_sprites[1] = Infos(33.2, 18, "./assets/r-player-2.png");
        _player_sprites[2] = Infos(33.2, 18, "./assets/r-player-3.png");
        _player_sprites[3] = Infos(33.2, 18, "./assets/r-player-4.png");
        _utils_sprites[0] = Infos(33.5, 35, "./assets/r-boom.png");
        _utils_sprites[1] = Infos(20, 20, "./assets/r-shoot.png");
    }

    void Game::run()
    {
        SystemManager manager;
        Frame current_frame;
        int mov;
        int shoot;
        int quit;
        int withSizeX = 800;
        int withSizeY = 600;
        int fps = 60;
        bool statusMenu = _menu.getStatusMenu();
        bool statusOpen = false;

        manager.addSystem<S_Renderer>(withSizeX, withSizeY, fps, "R-TYPE", "./assets/Purple/T_PurpleBackground_Version1_Layer");
        manager.addSystem<S_EventManager>();
        manager.addSystem<S_AudioManager>();
        createTextures();
        // auto backgroundMusic = manager.getSystem<S_AudioManager>()->getBackgroundMusic().find("THEME");
        // PlayMusicStream(backgroundMusic->second);
        while (manager.getSystem<S_Renderer>()->getStatusGame() != true) {
            if (statusMenu == true) {
               _menu.render(withSizeX);
               statusMenu = _menu.getStatusMenu();
                if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) {
                    std::cerr << "Thread Game voit que ca va soon arreter (in menu)" << std::endl;
                    manager.getSystem<S_Renderer>()->setStatusGame(true);
                }
            } else {
                manager.getSystem<S_Renderer>()->clearEntities();
                mov = manager.getSystem<S_EventManager>()->getMovement();
                shoot = manager.getSystem<S_EventManager>()->getShoot();
                quit = manager.getSystem<S_EventManager>()->getQuit();
                if (mov != 0 || shoot != 0 || quit != 0) {
                    if (shoot != 0) {
                        // auto effect = manager.getSystem<S_AudioManager>()->getSoundEffect().find("SHOOT");
                        // PlaySound(effect->second);
                    }
                    infoInteraction(mov, shoot, quit, 0); // à changer plus tard le 0 par l'info create Game
                }
                _mutex_frames.lock();
                if (_frames.size() != 0) {
                    current_frame.clearEntities();
                    current_frame = _frames.back();
                    _frames.pop_back();
                }
                _mutex_frames.unlock();
                // UpdateMusicStream(backgroundMusic->second);
                auto &entities = current_frame.getEntities();
                const auto& sparseIds = entities.getSparse();


                for (int id = 0; id < sparseIds.size(); ++id) {
                    if (sparseIds[id] != -1) {
                        auto& tmpEntity = entities.get(id);
                        if (typeid(tmpEntity) == typeid(E_Player)) {
                            auto it = _player_sprites.find(sparseIds[id]);
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_shared<C_Sprite>());
                            C_Sprite *sprite = dynamic_cast<C_Sprite*>(tmpEntity.getComponentOfType(typeid(C_Sprite)));
                            sprite->setupByTexture(infos._texture);
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});

                        } else if (typeid(tmpEntity) == typeid(E_Enemy)) {
                            C_EnemyInfo *ennemyInfo = Engine::getComponentRef<C_EnemyInfo>(tmpEntity);
                            if (ennemyInfo == nullptr)
                                continue;
                            auto it = _ennemy_sprites.find(ennemyInfo->_type);
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_shared<C_Sprite>());
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});
                            Engine::setSpriteTexture(tmpEntity, infos._texture);

                        } else if (typeid(tmpEntity) == typeid(E_Bullet)) {
                            auto it = _utils_sprites.find(1);
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_shared<C_Sprite>());
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});
                            Engine::setSpriteTexture(tmpEntity, infos._texture);
                        }
                        manager.getSystem<S_Renderer>()->addEntity(&tmpEntity);
                        manager.getSystem<S_Renderer>()->setIDServer(current_frame.getIDServer());
                    }
                }
                if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) {
                    manager.getSystem<S_Renderer>()->setStatusGame(true);
                }
                manager.update();
            }
        }
        CloseWindow();
        _statusGame = true;
    }

    Game::~Game() {
    }

    void Game::infoInteraction(int mov, int shoot, int quit, int createGame)
    {
        Interaction inter;

        // printf("Info with mov: %d, shoot: %d, quit: %d\n", mov, shoot, quit);
        _mutex_frames.lock();
        _mutex_interactions.lock();
        if (_frames.size() != 0 && _interactions.size() == 0) {
            inter.setInteraction(mov, shoot, quit, createGame);
            _interactions.push_back(inter);
        }
        _mutex_interactions.unlock();
        _mutex_frames.unlock();
    }

    void Menu::render(int screenWidth)
    {
        Rectangle btnCreate = { screenWidth/2 - 100, 100, 200, 50 };
        Rectangle btnSearch = { screenWidth/2 - 100, 200, 200, 50 };

        std::string errorMessage = "";

        std::vector<int> nbrPlayer;

        int hoveredParty = -1;

        Color violet = { 128, 0, 128, 255 };

        nbrPlayer = getIdGames();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (CheckCollisionPointRec(GetMousePosition(), btnCreate)) {
            DrawRectangleRec(btnCreate, violet);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                setCreateGame(true);
                if(errorMessage.empty()) {
                    setStatusMenu(false);
                    return;
                }
            }
        } else {
            DrawRectangleRec(btnCreate, LIGHTGRAY);
        }
        DrawText("Create new part", btnCreate.x + 10, btnCreate.y + 10, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), btnSearch)) {
            DrawRectangleRec(btnSearch, violet);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                setJoinGame(true);
            }
        } else {
            DrawRectangleRec(btnSearch, LIGHTGRAY);
        }
        DrawText("Search part", btnSearch.x + 10, btnSearch.y + 10, 20, BLACK);

        if (!errorMessage.empty()) {
            DrawText(errorMessage.c_str(), 10, 10, 20, RED);
        }

        for (int i = 0; i < nbrPlayer.size(); i++) {
            Rectangle partyRect = { screenWidth/2 - 100, 300 + 60 * i, 200, 50 };
            if (CheckCollisionPointRec(GetMousePosition(), partyRect)) {
                hoveredParty = i;
                DrawRectangleRec(partyRect, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    setSelectedParty(i);
                    setIdServerJoin(getSelectedParty());
                    setJoinGame(true);
                }
            } else {
                DrawRectangleRec(partyRect, WHITE);
            }
            if (getSelectedParty() == i) {
                DrawRectangleLinesEx(partyRect, 2, RED);
            }
            DrawText(std::to_string(nbrPlayer[i]).c_str(), partyRect.x + 10, partyRect.y + 10, 20, BLACK);
        }
        EndDrawing();
    }
}

void client::Frame::deserializeFrame(const std::vector<char>& serializedData) {
    auto it = serializedData.begin();
    E_Player player(0, 0, 0, 0);
    E_Enemy enemy(0, 0, 0, 0, 0);
    E_Bullet bullet(0, 0, 0, 0, 0, 0, 0, 0);
    int id_client = 1;
    size_t offset = 0;
    int uwu = 0;

    std::memcpy(&uwu, serializedData.data() + offset, sizeof(uwu));
    offset += sizeof(uwu);
    //printf("uwu = %d\n", uwu);

    if (std::distance(it, serializedData.end()) >= sizeof(_tick)) {
        std::memcpy(&_tick, &(*it), sizeof(_tick));
        //printf("tick = %d\n", _tick);
        it += sizeof(_tick);
    }
    if (std::distance(it, serializedData.end()) >= sizeof(_gameId)) {
        _gameId = *reinterpret_cast<const int*>(&(*it));
        // printf("serverId = %d\n", _serverId);
        it += sizeof(_gameId);
    }
    while (it < serializedData.end() && !isEndMarker(it, serializedData)) {
        std::string entityType;
        while (it != serializedData.end() && *it != '\0') {
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

            if (transform == nullptr || health == nullptr || hitbox == nullptr || score == nullptr)
                continue;
            auto playerShared = std::make_shared<E_Player>(transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y);
            playerShared->setId(id_client);
            Engine::setScore(*playerShared, score->score);
            int id = _entities.add(playerShared, id_client);
            id_client += 1;
        } else if (entityType == "E_Enemy") {
            // printf("deserialize enemy\n");
            size_t size_enemy = sizeof(C_Transform) + sizeof(C_Health) + sizeof(C_Hitbox) + sizeof(C_EnemyInfo);
            enemy.deserializeFromVector(std::vector<char>(it, it + size_enemy));
            it += sizeof(size_enemy);

            C_Transform *transform = Engine::getComponentRef<C_Transform>(enemy);
            C_Health *health = Engine::getComponentRef<C_Health>(enemy);
            C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(enemy);
            C_EnemyInfo *ennemyInfo = Engine::getComponentRef<C_EnemyInfo>(enemy);

            if (transform == nullptr || health == nullptr || hitbox == nullptr || ennemyInfo == nullptr)
                continue;
            auto enemyShared = std::make_shared<E_Enemy>(transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y, ennemyInfo->_type);
            int id = _entities.add(enemyShared);
            enemyShared->setId(id);

        } else if (entityType == "E_Bullet") {
            size_t size_bullet = sizeof(C_Transform) + sizeof(C_Damage) + sizeof(C_Hitbox);
            bullet.deserializeFromVector(std::vector<char>(it, it + size_bullet));
            it += sizeof(size_bullet);

            C_Transform *transform = Engine::getComponentRef<C_Transform>(bullet);
            C_Damage *damage = Engine::getComponentRef<C_Damage>(bullet);
            C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(bullet);

            auto bulletShared = std::make_shared<E_Bullet>(damage->_damage, transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y, transform->_velocity.x, transform->_velocity.y, 0);
            int id = _entities.add(bulletShared);
            bulletShared->setId(id);
        }

        if (isEndMarker(it, serializedData)) {
            break;
        }
    }
}

/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "../include/Game.hpp"

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

        manager.addSystem<S_Renderer>(withSizeX, withSizeY, fps, "R-TYPE", "./assets/Purple/T_PurpleBackground_Version1_Layer");
        manager.addSystem<S_EventManager>();
        manager.addSystem<S_AudioManager>();
        createTextures();
        auto backgroundMusic = manager.getSystem<S_AudioManager>()->getBackgroundMusic().find("THEME");
        PlayMusicStream(backgroundMusic->second);
        while (1) {
            if (statusMenu == true) {
                _menu.render(withSizeX);
                statusMenu = _menu.getStatusMenu();
            } else {
                manager.getSystem<S_Renderer>()->clearEntities();
                mov = manager.getSystem<S_EventManager>()->getMovement();
                shoot = manager.getSystem<S_EventManager>()->getShoot();
                quit = manager.getSystem<S_EventManager>()->getQuit();
                if (mov != 0 || shoot != 0 || quit != 0)
                    if (shoot != 0) {
                        auto effect = manager.getSystem<S_AudioManager>()->getSoundEffect().find("SHOOT");
                        PlaySound(effect->second);
                    }
                    infoInteraction(mov, shoot, quit, 0); // à changer plus tard le 0 par l'info create Game
                _mutex_frames.lock();
                if (_frames.size() != 0) {
                    current_frame.clearEntities();
                    current_frame = _frames.back();
                    _frames.pop_back();
                }
                _mutex_frames.unlock();
                UpdateMusicStream(backgroundMusic->second);
                auto &entities = current_frame.getEntities();
                const auto& sparseIds = entities.getSparse();


                for (int id = 0; id < sparseIds.size(); ++id) {
                    if (sparseIds[id] != -1) {
                        auto& tmpEntity = entities.get(id);
                        if (typeid(tmpEntity) == typeid(E_Player)) {
                            auto it = _player_sprites.find(sparseIds[id]);
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_unique<C_Sprite>());
                            C_Sprite *sprite = dynamic_cast<C_Sprite*>(tmpEntity.getComponentOfType(typeid(C_Sprite)));
                            sprite->setupByTexture(infos._texture);
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});

                        } else if (typeid(tmpEntity) == typeid(E_Enemy)) {
                            C_EnemyInfo *ennemyInfo = Engine::getComponentRef<C_EnemyInfo>(tmpEntity);
                            auto it = _ennemy_sprites.find(ennemyInfo->_type);
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_unique<C_Sprite>());
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});
                            Engine::setSpriteTexture(tmpEntity, infos._texture);

                        } else if (typeid(tmpEntity) == typeid(E_Bullet)) {
                            auto it = _utils_sprites.find(1);
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_unique<C_Sprite>());
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});
                            Engine::setSpriteTexture(tmpEntity, infos._texture);
                        }
                        manager.getSystem<S_Renderer>()->addEntity(&tmpEntity);
                        manager.getSystem<S_Renderer>()->setIDServer(current_frame.getIDServer());
                    }
                }
                manager.update();
            }
        }
    }

    Game::~Game() {
        for (auto it = _ennemy_sprites.begin(); it != _ennemy_sprites.end(); ++it) {
            UnloadTexture(it->second._texture);
            UnloadImage(it->second._image);
        }
        for (auto it = _player_sprites.begin(); it != _player_sprites.end(); ++it) {
            UnloadTexture(it->second._texture);
            UnloadImage(it->second._image);
        }
        for (auto it = _utils_sprites.begin(); it != _utils_sprites.end(); ++it) {
            UnloadTexture(it->second._texture);
            UnloadImage(it->second._image);
        }
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
        Rectangle btnJoin = { screenWidth/2 - 100, 200, 200, 50 };

        std::string errorMessage = "";
        std::string numberInput = "";

        bool inputActive = false;

        const int parties[] = { 178946, 2789456, 34561 };

        int selectedParty = -1;
        int hoveredParty = -1;

        Color violet = { 128, 0, 128, 255 };

        while (1) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            if (CheckCollisionPointRec(GetMousePosition(), btnCreate)) {
                DrawRectangleRec(btnCreate, violet);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    //mutex
                    //renvoie de l'erreur c'est il y en a une!
                    if (!errorMessage.empty()) {
                        DrawText(errorMessage.c_str(), 10, 10, 20, RED);
                    } else {
                        printf("create part\n");
                        this->_status = false;
                        return;
                    }
                }
            } else {
                DrawRectangleRec(btnCreate, LIGHTGRAY);
            }
                DrawText("Create new part", btnCreate.x + 10, btnCreate.y + 10, 20, BLACK);
                if (CheckCollisionPointRec(GetMousePosition(), btnJoin)) {
                    DrawRectangleRec(btnJoin, GRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedParty != -1) {
                    //mutex
                    //renvoie de l'erreur c'est il y en a une!
                    if (!errorMessage.empty()) {
                        DrawText(errorMessage.c_str(), 10, 10, 20, RED);
                    } else {
                        this->_JoinGame = true;
                        this->_idServerJoin = parties[selectedParty];
                        this->_status = false;
                        printf("Join part\n");
                        return;
                    }
                } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && std::stoi(numberInput) > 0) {
                    //mutex
                    //renvoie de l'erreur c'est il y en a une!
                    if (!errorMessage.empty()) {
                        DrawText(errorMessage.c_str(), 10, 10, 20, RED);
                    } else {
                        this->_JoinGame = true;
                        this->_idServerJoin = std::stoi(numberInput);
                        this->_status = false;
                        printf("Join part\n");
                        return;
                    }
                }
            } else {
                DrawRectangleRec(btnJoin, LIGHTGRAY);
        }
        DrawText("Join part", btnJoin.x + 10, btnJoin.y + 10, 20, BLACK);


        Rectangle inputRect = { screenWidth/2 - 100, 500, 200, 50 };
        DrawRectangleRec(inputRect, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), inputRect)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                inputActive = true;
            }
        }
        if (inputActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= '0' && key <= '9')) {
                    numberInput.push_back((char)key);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !numberInput.empty()) {
                numberInput.pop_back();
            }
        }
        DrawText(numberInput.c_str(), inputRect.x + 5, inputRect.y + 5, 20, BLACK);
        for (int i = 0; i < 3; i++) {
            Rectangle partyRect = { screenWidth/2 - 100, 300 + 60 * i, 200, 50 };
            if (CheckCollisionPointRec(GetMousePosition(), partyRect)) {
                hoveredParty = i;
                DrawRectangleRec(partyRect, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedParty = i;
                }
            } else {
                DrawRectangleRec(partyRect, WHITE);
            }
            if (selectedParty == i) {
                DrawRectangleLinesEx(partyRect, 2, RED);
            }
            DrawText(std::to_string(parties[i]).c_str(), partyRect.x + 10, partyRect.y + 10, 20, BLACK);
        }
        EndDrawing();
        }
    }
}

void client::Frame::deserializeFrame(const std::vector<char>& serializedData) {
    auto it = serializedData.begin();
    E_Player player(0, 0, 0, 0);
    E_Enemy enemy(0, 0, 0, 0, 0);
    E_Bullet bullet(0, 0, 0, 0, 0, 0, 0, 0);
    int id_client = 1;

    if (std::distance(it, serializedData.end()) >= sizeof(_tick)) {
        _tick = *reinterpret_cast<const int*>(&(*it));
        // printf("tick = %d\n", _tick);
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

            auto playerShared = std::make_shared<E_Player>(transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y);
            playerShared->setId(id_client);
            Engine::setScore(*playerShared, score->_score);
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

            auto enemyShared = std::make_shared<E_Enemy>(transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y, ennemyInfo->_type);
            int id = _entities.add(enemyShared);
            enemyShared->setId(id);

        } else if (entityType == "E_Bullet") {
            // printf("deserialize bullet\n");
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
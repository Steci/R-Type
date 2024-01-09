/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "../include/Game.hpp"

namespace client {
    void Game::actionUpCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    {
        if (entities.exists(clientID) == false) {
            printf("player not connected");
            return;
        }
        auto& playerEntity = entities.get(clientID);
        interaction->setInteraction(1);
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            Engine::setTransformPos(playerEntity, {transform->_position.x, transform->_position.y - 10});
            if (transform->_animation == 3) {
                Engine::setTransformAni(playerEntity, 4);
            } else if (transform->_animation == 2) {
                Engine::setTransformAni(playerEntity, 1);
            } else if (transform->_animation == 1) {
                Engine::setTransformAni(playerEntity, 0);
            } else if (transform->_animation == 0) {
                Engine::setTransformAni(playerEntity, 3);
            } else {
                Engine::setTransformAni(playerEntity, 4);
            }
        }
    }

    void Game::actionDownCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    {
        if (entities.exists(clientID) == false) {
            printf("player not connected");
            return;
        }
        auto& playerEntity = entities.get(clientID);
        interaction->setInteraction(3);
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            Engine::setTransformPos(playerEntity, {transform->_position.x, transform->_position.y + 10});
            if (transform->_animation == 1) {
                Engine::setTransformAni(playerEntity, 2);
            } else if (transform->_animation == 4) {
                Engine::setTransformAni(playerEntity, 3);
            } else if (transform->_animation == 3) {
                Engine::setTransformAni(playerEntity, 0);
            } else if (transform->_animation == 0) {
                Engine::setTransformAni(playerEntity, 1);
            } else {
                Engine::setTransformAni(playerEntity, 2);
            }
        }
    }

    void Game::actionLeftCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    {
        if (entities.exists(clientID) == false) {
            printf("player not connected");
            return;
        }
        auto& playerEntity = entities.get(clientID);
        interaction->setInteraction(4);
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            Engine::setTransformPos(playerEntity, {transform->_position.x - 10, transform->_position.y});
            if (transform->_animation == 2) {
                Engine::setTransformAni(playerEntity, 1);
            } else if (transform->_animation == 4) {
                Engine::setTransformAni(playerEntity, 3);
            } else {
                Engine::setTransformAni(playerEntity, 0);
            }
        }
    }

    void Game::actionRightCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    {
        if (entities.exists(clientID) == false) {
            printf("player not connected");
            return;
        }
        auto& playerEntity = entities.get(clientID);
        interaction->setInteraction(2);
        C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        if (transform) {
            Engine::setTransformPos(playerEntity, {transform->_position.x + 10, transform->_position.y});
            if (transform->_animation == 2) {
                Engine::setTransformAni(playerEntity, 1);
            } else if (transform->_animation == 4) {
                Engine::setTransformAni(playerEntity, 3);
            } else {
                Engine::setTransformAni(playerEntity, 0);
            }
        }
    }

    void Game::actionQuitCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    {
        if (entities.exists(clientID) == false) {
            printf("player not connected");
            return;
        }
        auto& playerEntity = entities.get(clientID);
        interaction->setInteraction(0, 0, 1);
        entities.remove(clientID);
    }

    //void Game::actionConnectCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    //{
    //    int nbrPlayer = 0;
    //    const auto& sparseIds = entities.getAllIndices();
    //    for (auto id : sparseIds) {
    //        if (id != -1) {
    //            auto& tmpEntity = entities.get(id);
    //            if (typeid(tmpEntity) == typeid(E_Player)) {
    //                nbrPlayer++;
    //            }
    //        }
    //    }
    //    if (nbrPlayer >= 4)
    //        return;
    //    if (entities.exists(clientID) == true) {
    //        printf("player already connected");
    //        return;
    //    }
    //    // create entity
    //    std::string path = "./assets/r-typesheet42.png";
    //    entities.add(std::make_shared<E_Player>(path, 50, 50, 33.2, 17.2), clientID);
    //    auto& playerEntity = entities.get(clientID);
    //    // add entity to entities
    //}

    void Game::actionShootCommand(int clientID, SparseArray<IEntity>& entities, Interaction *interaction)
    {
        if (entities.exists(clientID) == false) {
            printf("player not connected");
            return;
        }
        interaction->setInteraction(0, 1, 0);
        //cote server -> a voir pour le system de music
        //E_Player& playerEntity = static_cast<E_Player&>(entities.get(clientID));
        //if (typeid(playerEntity) == typeid(E_Player)) {
        //    C_Transform *transform = Engine::getComponentRef<C_Transform>(playerEntity);
        //    playerEntity.newShoot("./assets/r-typesheet24.png", 10, transform->_position.x + 10, transform->_position.y + 2, transform->_size.x, transform->_size.y, 5, 0);
        //}
        //auto effect = manager.getSystem<S_AudioManager>()->getSoundEffect().find("SHOOT");
        //PlaySound(effect->second);
    }

    // void server::Game::actionDamageCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
    // {
    //     printf("damage");
    //     if (entities.exists(clientID) == false) {
    //         printf("player not connected");
    //         return;
    //     }
    //     auto& entity = entities.get(clientID);
    //     C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(entity);
    //     C_Health *health = Engine::getComponentRef<C_Health>(entity);
    //     if (health->_health <= 0) {
    //         Engine::setHitboxStatus(entity, 2);
    //         std::string dead_path = "./assets/r-typesheet1.png";
    //         Image newImage = LoadImage(dead_path.c_str());
    //         if (newImage.data == nullptr) {
    //             std::cerr << "Erreur de chargement de l'image : " << dead_path << std::endl;
    //         }
    //         Engine::setSpriteImage(entity, newImage);
    //         Texture2D newTexture = LoadTextureFromImage(newImage);
    //         Engine::setSpriteTexture(entity, newTexture);
    //         C_Transform *transform = Engine::getComponentRef<C_Transform>(entity);
    //         Engine::setTransformSize(entity, {33.25, 345});
    //         Engine::setTransformAni(entity, 0);
    //     } else {
    //         Engine::setHealth(entity, health->_health - 10);
    //         Engine::setHitboxStatus(entity, 1);
    //     }
    // }

    // void server::Game::actionScoreCommand(int clientID, SystemManager manager, SparseArray<IEntity>& entities)
    // {
    //     printf("score");
    //     if (entities.exists(clientID) == false) {
    //         printf("player not connected");
    //         return;
    //     }
    //     auto& playerEntity = entities.get(clientID);
    //     if (typeid(playerEntity) == typeid(E_Player)) {
    //         C_Score *score = Engine::getComponentRef<C_Score>(playerEntity);
    //         Engine::setScore(playerEntity, score->_score + 10);
    //     }
    // }

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
        _utils_sprites[1] = Infos(33, 18, "./assets/r-shoot.png");
    }

    void Game::run()
    {
        SystemManager manager;
        Frame current_frame;
        int mov;
        int shoot;
        int quit;

        manager.addSystem<S_Renderer>(800, 600, 60, "R-TYPE", "./assets/Purple/T_PurpleBackground_Version1_Layer");
        manager.addSystem<S_EventManager>();
        createTextures();
        //detruire toutes les texture à la fin du jeu
        while (1) {
            manager.getSystem<S_Renderer>()->clearEntities();
            // printf("Key pressed : %d\n", manager.getSystem<S_EventManager>()->EventKeyPressed(std::list<int>{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE}));
            mov = manager.getSystem<S_EventManager>()->getMovement();
            shoot = manager.getSystem<S_EventManager>()->getShoot();
            quit = manager.getSystem<S_EventManager>()->getQuit();
            infoInteraction(mov, shoot, quit);
            _mutex_frames.lock();
            if (_frames.size() != 0) {
                current_frame.clearEntities();
                // std::cout << "frame tick : " << _frames.back().getTick() << std::endl;
                current_frame = _frames.back();
                _frames.pop_back();
            }
            _mutex_frames.unlock();
            auto &entities = current_frame.getEntities();
            const auto& sparseIds = entities.getAllIndices();
            for (auto id : sparseIds) {
                if (id != -1) {
                    auto& tmpEntity = entities.get(id);
                    if (typeid(tmpEntity) == typeid(E_Player)) {
                        auto it = _player_sprites.find(id);
                        if (it != _player_sprites.end()) {
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_unique<C_Sprite>());
                            C_Sprite *sprite = dynamic_cast<C_Sprite*>(tmpEntity.getComponentOfType(typeid(C_Sprite)));
                            sprite->setupByTexture(infos._texture);
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});
                        }
                    } else if (typeid(tmpEntity) == typeid(E_Enemy)) {
                        C_EnemyInfo *ennemyInfo = Engine::getComponentRef<C_EnemyInfo>(tmpEntity);
                        auto it = _ennemy_sprites.find(ennemyInfo->_type);
                        if (it != _ennemy_sprites.end()) {
                            auto infos = it->second;
                            tmpEntity.addComponent(std::make_unique<C_Sprite>());
                            Engine::setTransformSize(tmpEntity, {infos._size.x, infos._size.y});
                            Engine::setSpriteTexture(tmpEntity, infos._texture);
                        }
                    }
                    // std::cout << "entity pos x: " << tmpEntity.getComponentOfType(typeid(C_Transform))._position.x << " y: " << tmpEntity.getComponentOfType(typeid(C_Transform))->position_y << std::endl;
                    // printf("pos x = %f, pos y = %f\n", Engine::getComponentRef<C_Transform>(tmpEntity)->_position.x, Engine::getComponentRef<C_Transform>(tmpEntity)->_position.y);
                    manager.getSystem<S_Renderer>()->addEntity(&tmpEntity);
                }
            }
            manager.update();
            //tout le bordel d'affichage + détection de touches
        }
    }

    void Game::testInteraction()
    {
        Interaction inter;

        _mutex_frames.lock();
        _mutex_interactions.lock();
        if (_frames.size() != 0 && _frames.back().getTick() == 100 && _interactions.size() == 0) {
            std::cout << "test interaction" << std::endl;
            inter.setInteraction(1);
            _interactions.push_back(inter);
        }
        _mutex_interactions.unlock();
        _mutex_frames.unlock();
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

    void Game::infoInteraction(int mov, int shoot, int quit)
    {
        Interaction inter;

        // printf("Info with mov: %d, shoot: %d, quit: %d\n", mov, shoot, quit);
        _mutex_frames.lock();
        _mutex_interactions.lock();
        if (_frames.size() != 0 && _interactions.size() == 0) {
            inter.setInteraction(mov, shoot, quit);
            _interactions.push_back(inter);
        }
        _mutex_interactions.unlock();
        _mutex_frames.unlock();
    }
}

void client::Frame::deserializeFrame(const std::vector<char>& serializedData) {
    auto it = serializedData.begin();
    Vec2 pos;
    Vec2 size;
    Vec2 velocity;

    if (std::distance(it, serializedData.end()) >= sizeof(_tick)) {
        std::memcpy(&_tick, &it, sizeof(_tick));
        it += sizeof(_tick);
    }
    while (it < serializedData.end() && !isEndMarker(it, serializedData)) {
        std::string entityType;
        while (it != serializedData.end() && *it != '\0') {
            entityType.push_back(*it);
            ++it;
        }
        ++it;
        if (entityType == "E_Player") {
            pos.deserializeFromVector(std::vector<char>(it, it + sizeof(pos)));
            it += sizeof(pos);
            size.deserializeFromVector(std::vector<char>(it, it + sizeof(size)));
            it += sizeof(size);
            auto player = std::make_shared<E_Player>(pos.x, pos.y, size.x, size.y);
            _entities.add(player);
        } else if (entityType == "E_Enemy") {
            pos.deserializeFromVector(std::vector<char>(it, it + sizeof(pos)));
            it += sizeof(pos);
            size.deserializeFromVector(std::vector<char>(it, it + sizeof(size)));
            it += sizeof(size);

            auto enemy = std::make_shared<E_Enemy>(pos.x, pos.y, size.x, size.y);
            _entities.add(enemy);
        } else if (entityType == "E_Bullet") {
            int damage;
            std::memcpy(&damage, &it, sizeof(damage));
            it += sizeof(damage);
            pos.deserializeFromVector(std::vector<char>(it, it + sizeof(pos)));
            it += sizeof(pos);
            size.deserializeFromVector(std::vector<char>(it, it + sizeof(size)));
            it += sizeof(size);
            velocity.deserializeFromVector(std::vector<char>(it, it + sizeof(velocity)));
            it += sizeof(velocity);
            int idCreator;
            std::memcpy(&idCreator, &it, sizeof(idCreator));
            it += sizeof(idCreator);

            auto bullet = std::make_shared<E_Bullet>(damage, pos.x, pos.y, size.x, size.y, velocity.x, velocity.y, idCreator);
            _entities.add(bullet);
        }
        if (isEndMarker(it, serializedData)) {
            break;
        }
    }
}
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
        _player_sprites[1] = Infos(33.2, 18, "./assets/r-player-1.png");
        _player_sprites[2] = Infos(33.2, 18, "./assets/r-player-2.png");
        _player_sprites[3] = Infos(33.2, 18, "./assets/r-player-3.png");
        _player_sprites[4] = Infos(33.2, 18, "./assets/r-player-4.png");
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
            if (mov != 0 || shoot != 0 || quit != 0)
                infoInteraction(mov, shoot, quit);
            _mutex_frames.lock();
            if (_frames.size() != 0) {
                current_frame.clearEntities();
                // std::cout << "frame tick : " << _frames.back().getTick() << std::endl;
                current_frame = _frames.back();
                // bool print = false;
                // for (auto it : current_frame.getEntities().getAll()) {
                //     auto& entity = *it;
                //     if (typeid(entity) == typeid(E_Bullet)) {
                //         print = true;
                //         C_Transform *transform = Engine::getComponentRef<C_Transform>(entity);
                //         printf("Bullet Y:%f ", transform->_position.y);
                //     }
                // }
                // if (print)
                //     printf("\n");
                _frames.pop_back();
            }
            _mutex_frames.unlock();
            auto &entities = current_frame.getEntities();
            const auto& sparseIds = entities.getSparse();
            for (int id = 0; id < sparseIds.size(); ++id) {
                if (sparseIds[id] != -1) {
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
                    } else if (typeid(tmpEntity) == typeid(E_Bullet)) {
                        auto it = _utils_sprites.find(1);
                        if (it != _utils_sprites.end()) {
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
    E_Player player(0, 0, 0, 0);
    E_Enemy enemy(0, 0, 0, 0, 0);
    E_Bullet bullet(0, 0, 0, 0, 0, 0, 0, 0);

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
            size_t size_player = sizeof(C_Transform) + sizeof(C_Health) + sizeof(C_Hitbox) + sizeof(C_Score);
            player.deserializeFromVector(std::vector<char>(it, it + size_player));
            it += sizeof(size_player);
            C_Transform *transform = Engine::getComponentRef<C_Transform>(player);
            C_Health *health = Engine::getComponentRef<C_Health>(player);
            C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(player);
            C_Score *score = Engine::getComponentRef<C_Score>(player);
            auto playerShared = std::make_shared<E_Player>(player);
            _entities.add(playerShared);
        } else if (entityType == "E_Enemy") {
            size_t size_enemy = sizeof(C_Transform) + sizeof(C_Health) + sizeof(C_Hitbox) + sizeof(C_EnemyInfo);
            enemy.deserializeFromVector(std::vector<char>(it, it + size_enemy));
            it += sizeof(size_enemy);
            C_Transform *transform = Engine::getComponentRef<C_Transform>(enemy);
            C_Health *health = Engine::getComponentRef<C_Health>(enemy);
            C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(enemy);
            C_EnemyInfo *ennemyInfo = Engine::getComponentRef<C_EnemyInfo>(enemy);
            auto enemyShared = std::make_shared<E_Enemy>(transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y, ennemyInfo->_type);
            _entities.add(enemyShared);
        } else if (entityType == "E_Bullet") {
            size_t size_bullet = sizeof(C_Transform) + sizeof(C_Damage) + sizeof(C_Hitbox) + sizeof(int);
            bullet.deserializeFromVector(std::vector<char>(it, it + sizeof(bullet)));
            it += sizeof(bullet);
            auto bulletShared = std::make_shared<E_Bullet>(bullet);
            // float bulletY = dynamic_cast<C_Transform*>(bulletShared->getComponentOfType(typeid(C_Transform)))->_position.y;
            // printf("bullet pos y = %f\n", bulletY);
            _entities.add(bulletShared);
        }
        if (isEndMarker(it, serializedData)) {
            break;
        }
    }
}
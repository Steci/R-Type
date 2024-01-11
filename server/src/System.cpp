/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include <sstream>
#include <algorithm>
#include <cmath>
#include "Game.hpp"

S_Collision::S_Collision(SparseArray<IEntity> &sparseEntities)
    : _sparseEntities(sparseEntities)
{
}

bool S_Collision::checkCollision(C_Transform* transform1, C_Transform* transform2, C_Hitbox* hitbox1, C_Hitbox* hitbox2)
{
    float left1 = transform1->_position.x;
    float right1 = transform1->_position.x + hitbox1->_size.x;
    float top1 = transform1->_position.y;
    float bottom1 = transform1->_position.y + hitbox1->_size.y;

    float left2 = transform2->_position.x;
    float right2 = transform2->_position.x + hitbox2->_size.x;
    float top2 = transform2->_position.y;
    float bottom2 = transform2->_position.y + hitbox2->_size.y;

    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true;
    }
    return false;
}

void S_Collision::update()
{
    for (auto& entity1 : _sparseEntities.getAll()) {
        printf("Before line 1\n");
        for (auto& entity2 : _sparseEntities.getAll()) {
            printf("Before line 2\n");
            if (entity1 != entity2) {
                printf("Before line 3\n");
                // print ALL the info about the entities
                // print the denseIndex of the entities
                for (auto& entity : _sparseEntities.getAll()) {
                    printf("Entity ID: %d\n", entity->getId());
                }
                printf("start printing specific\n");
                printf("Entity1 type: %s\n", typeid(*entity1).name());
                printf("Entity1 ID: %d\n", entity1->getId());
                printf("Entity2 ID: %d\n", entity2->getId());
                printf("Entity1 Type: %s\n", entity1->getType().c_str());
                printf("Entity2 Type: %s\n", entity2->getType().c_str());
                C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);
                printf("Before line 4\n");
                C_Hitbox* hitbox2 = Engine::getComponentRef<C_Hitbox>(*entity2);
                printf("Before line 5\n");
                C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);
                printf("Before line 6\n");
                C_Transform* transform2 = Engine::getComponentRef<C_Transform>(*entity2);
                printf("Before line 7\n");

                if (typeid(*entity1) == typeid(E_Player) && typeid(*entity2) == typeid(E_Enemy)) {
                    printf("Before line 8\n");
                    if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {
                        printf("Before line 9\n");
                        C_Health* health1 = Engine::getComponentRef<C_Health>(*entity1);
                        printf("Before line 10\n");
                        C_Health* health2 = Engine::getComponentRef<C_Health>(*entity2);

                        printf("Before line 11\n");
                        transform1->_position.x -= 50;
                        printf("Before line 12\n");
                        _sparseEntities.remove(entity2->getId());
                        printf("After line 12\n");
                    }
                }
                else if (typeid(*entity1) == typeid(E_Bullet) && typeid(*entity2) == typeid(E_Enemy)) {
                    printf("Before line 13\n");
                    if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {
                        printf("Before line 14\n");
                        C_Health* health2 = Engine::getComponentRef<C_Health>(*entity2);
                        printf("Before line 15\n");
                        C_Damage* damage1 = Engine::getComponentRef<C_Damage>(*entity1);

                        printf("Before line 16\n");
                        _sparseEntities.remove(entity1->getId());
                        printf("Before line 17\n");
                        _sparseEntities.remove(entity2->getId());
                        printf("After line 17\n");
                    }
                }
            }
        }
        if (typeid(*entity1) == typeid(E_Player)) {
            printf("Before line 18\n");
            // check if player is leaving screenWidth or screenHeight
            C_Transform* transform1 = Engine::getComponentRef<C_Transform>(*entity1);
            printf("Before line 19\n");
            C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(*entity1);

            printf("Before line 20\n");
            if (transform1->_position.x < 0)
                transform1->_position.x = 0;
            printf("Before line 21\n");
            if (transform1->_position.x + hitbox1->_size.x > screenWidth)
                transform1->_position.x = screenWidth - hitbox1->_size.x;
            printf("Before line 22\n");
            if (transform1->_position.y < 0)
                transform1->_position.y = 0;
            printf("Before line 23\n");
            if (transform1->_position.y + hitbox1->_size.y > screenHeight)
                transform1->_position.y = screenHeight - hitbox1->_size.y;
            printf("After line 23\n");
        }
        if (typeid(*entity1) == typeid(E_Enemy)) {
            printf("Before line 24\n");
            // Destroy enemy if it leaves the screen on the left
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity1);

            printf("Before line 25\n");
            if (transform->_position.x <= -100.0) {
                printf("Before line 26\n");
                int id = entity1->getId();
                printf("Enemy %d destroyed (POS X:%f Y:%f)\n", id, transform->_position.x, transform->_position.y);
                printf("Before line 27\n");
                _sparseEntities.remove(id);
                printf("After line 27\n");
            }
        }
        else if (typeid(*entity1) == typeid(E_Bullet)) {
            printf("Before line 28\n");
            // Destroy bullet if it leaves the screen
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity1);

            printf("Before line 29\n");
            if (transform->_position.x >= screenWidth + 10 || transform->_position.y >= screenHeight + 10 || transform->_position.y <= -10.0 || transform->_position.x <= -10.0) {
                printf("Before line 30\n");
                // printf("Bullet %d destroyed\n", entity1->getId());
                printf("Bullet %d destroyed\n", entity1->getId());
                printf("Before line 31\n");
                _sparseEntities.remove(entity1->getId());
                printf("After line 31\n");
            }
        }
    }
}

S_EnemyAI::S_EnemyAI(SparseArray<IEntity> &sparseEntities )
    : _sparseEntities(sparseEntities)
{
}

void S_EnemyAI::update()
{
    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Enemy)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity);
            C_EnemyInfo* enemyInfo = Engine::getComponentRef<C_EnemyInfo>(*entity);

            if (enemyInfo->_type == 1) {
                // straight line
                transform->_position.x -= 5;
            }
            if (enemyInfo->_type == 2) {
                // the enemy will move in a sinusoid pattern
                transform->_position.x -= 5;
                transform->_position.y = 20 * sin(transform->_position.x / 30) + transform->_position.y;
            }
            if (enemyInfo->_type == 3) {
                // the enemy will move in a sinusoid pattern but smaller and faster
                transform->_position.x -= 8;
                transform->_position.y = 10 * sin(transform->_position.x / 20) + transform->_position.y;
            }
        }
    }
}

S_Spawner::S_Spawner(SparseArray<IEntity> &sparseEntities)
    : _sparseEntities(sparseEntities)
{
}

void S_Spawner::update()
{
    int random = rand() % 50;

    if (random == 1 || random == 50) {
        int random2 = rand() % 3;
        int random4 = rand() % 600;
        int random5 = rand() % 3 + 1;
        int random3 = rand() % (random5 == 1 ? 400 : 600);
        std::shared_ptr<E_Enemy> enemy = std::make_shared<E_Enemy>(800, random3, 65, 66, random5);
        int id = _sparseEntities.add(enemy);
        enemy->setId(id);
        printf("Creating Enemy ID: %d with type %d\n", id, random2);
    }
}

S_Weapon::S_Weapon(SparseArray<IEntity> &sparseEntities, int &tick)
   : _sparseEntities(sparseEntities) , _tick(tick)
{
}

void S_Weapon::shootPlayer(int idCreator)
{
    if (_tick - _lastTick < 10) {
        return;
    }

    int i = 0;

    for (auto& entity : _sparseEntities.getAll()) {
        if (idCreator == entity->getId()) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity);
            // create bullet with player position info
            int xpos = transform->_position.x + transform->_size.x;
            int ypos = transform->_position.y + transform->_size.y / 2;
            // printf("Player position : %d %d\n", xpos, ypos);
            float velocity_x = 20;
            float velocity_y = 0;
            std::shared_ptr<E_Bullet> bullet = std::make_shared<E_Bullet>(0, xpos, ypos, 10, 10, velocity_x, velocity_y, idCreator);
            int id = _sparseEntities.add(bullet);
            bullet->setId(id);
            printf("Creating Bullet ID: %d\n", id);
            _lastTick = _tick;
        }
        i++;
    }
}

void S_Weapon::update()
{
    // Update all bullets

    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Bullet)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(*entity);

            transform->_position.x = static_cast<float>(transform->_position.x + transform->_velocity.x);
            transform->_position.y = static_cast<float>(transform->_position.y + transform->_velocity.y);
            // printf("Bullet %d position : %f %f\n", denseIndex[i], transform->_position.x, transform->_position.y);
        }
    }
}

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
    std::vector<int> toRemove;

    for (auto& entity1 : _sparseEntities.getAll()) {
        for (auto& entity2 : _sparseEntities.getAll()) {
            if (entity1 != entity2) {
                C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(entity1.get());
                C_Hitbox* hitbox2 = Engine::getComponentRef<C_Hitbox>(entity2.get());
                C_Transform* transform1 = Engine::getComponentRef<C_Transform>(entity1.get());
                C_Transform* transform2 = Engine::getComponentRef<C_Transform>(entity2.get());

                if (hitbox1 == nullptr || hitbox2 == nullptr || transform1 == nullptr || transform2 == nullptr)
                    continue;
                if (typeid(*entity1) == typeid(E_Player) && typeid(*entity2) == typeid(E_Enemy)) {
                    if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {
                        C_Health* health1 = Engine::getComponentRef<C_Health>(entity1.get());
                        C_Health* health2 = Engine::getComponentRef<C_Health>(entity2.get());

                        if (health1 == nullptr || health2 == nullptr)
                            continue;
                        transform1->_position.x -= 50;
                        toRemove.push_back(entity2->getId());
                    }
                }
                else if (typeid(*entity1) == typeid(E_Bullet) && typeid(*entity2) == typeid(E_Enemy)) {
                    if (checkCollision(transform1, transform2, hitbox1, hitbox2)) {
                        C_Damage* damage1 = Engine::getComponentRef<C_Damage>(entity1.get());
                        C_EnemyInfo* enemyInfo = Engine::getComponentRef<C_EnemyInfo>(entity1.get());

                        int idCreator = dynamic_cast<E_Bullet*>(entity1.get())->getIdCreator();
                        C_Score* score = Engine::getComponentRef<C_Score>(&_sparseEntities.get(idCreator));
                        toRemove.push_back(entity1->getId());
                        toRemove.push_back(entity2->getId());
                        if (enemyInfo && enemyInfo->_type == 1 && score) {
                            score->score += 10;
                        } else if (enemyInfo && enemyInfo->_type == 2 && score) {
                            score->score += 20;
                        } else if (score) {
                            score->score += 30;
                        }
                        Engine::setScore(_sparseEntities.get(idCreator), score->score);
                    }
                }
            }
        }
        if (typeid(*entity1) == typeid(E_Player)) {
            C_Transform* transform1 = Engine::getComponentRef<C_Transform>(entity1.get());
            C_Hitbox* hitbox1 = Engine::getComponentRef<C_Hitbox>(entity1.get());

            if (transform1 == nullptr || hitbox1 == nullptr)
                continue;
            if (transform1->_position.x < 0)
                transform1->_position.x = 0;
            if (transform1->_position.x + hitbox1->_size.x > screenWidth)
                transform1->_position.x = screenWidth - hitbox1->_size.x;
            if (transform1->_position.y < 0)
                transform1->_position.y = 0;
            if (transform1->_position.y + hitbox1->_size.y > screenHeight)
                transform1->_position.y = screenHeight - hitbox1->_size.y;
        }
        if (typeid(*entity1) == typeid(E_Enemy)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(entity1.get());

            if (transform == nullptr)
                continue;
            if (transform->_position.x <= -100.0) {
                int id = entity1->getId();
                toRemove.push_back(id);
            }
        }
        else if (typeid(*entity1) == typeid(E_Bullet)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(entity1.get());

            if (transform == nullptr)
                continue;
            if (transform->_position.x >= screenWidth + 10 || transform->_position.y >= screenHeight + 10 || transform->_position.y <= -10.0 || transform->_position.x <= -10.0) {
                toRemove.push_back(entity1->getId());
            }
        }
    }
    for (auto& id : toRemove) {
        _sparseEntities.remove(id);
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
            C_Transform* transform = Engine::getComponentRef<C_Transform>(entity.get());
            C_EnemyInfo* enemyInfo = Engine::getComponentRef<C_EnemyInfo>(entity.get());

            if (transform == nullptr || enemyInfo == nullptr)
                return;
            if (enemyInfo->_type == 1) {
                transform->_position.x -= (8 * TICK_SPEED) / DESIRED_SPEED;
            }
            if (enemyInfo->_type == 2) {
                transform->_position.x -= (11 * TICK_SPEED) / DESIRED_SPEED;
                transform->_position.y = 10 * sin(transform->_position.x / (20 * TICK_SPEED / DESIRED_SPEED)) + transform->_position.y;
            }
            if (enemyInfo->_type == 3) {
                transform->_position.x -= (8 * TICK_SPEED) / DESIRED_SPEED;
                transform->_position.y = 20 * sin(transform->_position.x / (30 * TICK_SPEED / DESIRED_SPEED)) + transform->_position.y;
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
    int random = rand() % 200;

    if (random == 1 || random == 200) {
        int random2 = rand() % 3;
        int random4 = rand() % 600;
        int random5 = rand() % 3 + 1;
        int random3 = rand() % (random5 != 1 ? 400 : 600);
        std::shared_ptr<E_Enemy> enemy = std::make_shared<E_Enemy>(800, random3, 65, 66, random5);
        int id = _sparseEntities.add(enemy);
        enemy->setId(id);
    }
    if (random == 100) {
        int randomType = rand() % 3 + 1;
        int randomY = rand() % (randomType != 1 ? 400 : 600);
        int randomAmount = rand() % 4 + 1;
        for (int i = 0; i < randomAmount; i++) {
            std::shared_ptr<E_Enemy> enemy = std::make_shared<E_Enemy>(800 + (i * 50), randomY, 65, 66, randomType);
            int id = _sparseEntities.add(enemy);
            enemy->setId(id);
        }
    }
}

S_Weapon::S_Weapon(SparseArray<IEntity> &sparseEntities, int &tick)
   : _sparseEntities(sparseEntities) , _tick(tick)
{
}

void S_Weapon::shootPlayer(int idCreator)
{
    E_Player* player;
    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Player)) {
            if (entity->getId() == idCreator) {
                player = dynamic_cast<E_Player*>(entity.get());
            }
        }
    }
    int lastTick = player->getLastTick();
    if (_tick - lastTick < (_firingSpeed * TICK_SPEED) / DESIRED_SPEED) {
        return;
    }
    IEntity& entity = _sparseEntities.get(idCreator);
    if (&entity == nullptr) {
        return;
    }
    C_Transform* transform = Engine::getComponentRef<C_Transform>(&entity);
    if (transform == nullptr)
        return;
    int xpos = transform->_position.x + transform->_size.x;
    int ypos = transform->_position.y + transform->_size.y / 2;
    float velocity_x = 20;
    float velocity_y = 0;
    std::shared_ptr<E_Bullet> bullet = std::make_shared<E_Bullet>(0, xpos, ypos, 10, 10, velocity_x, velocity_y, idCreator);
    int id = _sparseEntities.add(bullet);
    bullet->setId(id);
    player->setLastTick(_tick);
}

void S_Weapon::update()
{
    for (auto& entity : _sparseEntities.getAll()) {
        if (typeid(*entity) == typeid(E_Player)) {
            C_Score* score = Engine::getComponentRef<C_Score>(entity.get());
            if (score == nullptr)
                continue;
            if (score->score >= 1000) {
                score->score -= 1000;
                Engine::setScore(*entity, score->score);
                if (getFiringSpeed() > 20)
                    setFiringSpeed(getFiringSpeed() - 2);
            }
        }
        if (typeid(*entity) == typeid(E_Bullet)) {
            C_Transform* transform = Engine::getComponentRef<C_Transform>(entity.get());

            if (transform == nullptr)
                continue;
            transform->_position.x = static_cast<float>(transform->_position.x + ((transform->_velocity.x * TICK_SPEED) / DESIRED_SPEED));
            transform->_position.y = static_cast<float>(transform->_position.y + ((transform->_velocity.y * TICK_SPEED) / DESIRED_SPEED));
        }
    }
}

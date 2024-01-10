/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.cpp
*/

#include <sstream>
#include <algorithm>
#include "Game.hpp"

E_Bullet::E_Bullet(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y, int idCreator)
{
    addComponent(std::make_shared<C_Transform>(position_x, position_y, size_x, size_y, velocity_x, velocity_y));
    addComponent(std::make_shared<C_Damage>(damage));
    addComponent(std::make_shared<C_Hitbox>(size_x, size_y));
    _idCreator = idCreator;
}

std::string E_Bullet::getType() const {
    return "E_Bullet";
}

std::vector<char> E_Bullet::serializeToVector()
{
    std::vector<char> data;

    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    // printf("Transform serialize X:%f Y:%f\n", transformComponent->_position.x, transformComponent->_position.y);
    if (transformComponent) {
        auto transformData = transformComponent->serializeToVector();
        data.insert(data.end(), transformData.begin(), transformData.end());
    }

    C_Damage* damageComponent = Engine::getComponentRef<C_Damage>(*this);
    if (damageComponent) {
        auto damageData = damageComponent->serializeToVector();
        data.insert(data.end(), damageData.begin(), damageData.end());
    }

    C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    if (hitboxComponent) {
        auto hitboxData = hitboxComponent->serializeToVector();
        data.insert(data.end(), hitboxData.begin(), hitboxData.end());
    }
    data.insert(data.end(), reinterpret_cast<const char*>(&_idCreator), reinterpret_cast<const char*>(&_idCreator) + sizeof(_idCreator));
    return data;
}

E_Player::E_Player(int position_x, int position_y, float size_x, float size_y)
{
    addComponent(std::make_shared<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
    addComponent(std::make_shared<C_Health>(100));
    addComponent(std::make_shared<C_Hitbox>(66, 34));
    addComponent(std::make_shared<C_Score>());
}

void E_Player::update()
{
    auto& transform = getComponents()[0];
    auto& health = getComponents()[1];
}

std::string E_Player::getType() const {
    return "E_Player";
}

std::vector<char> E_Player::serializeToVector()
{
    std::vector<char> data;
    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    C_Health* healthComponent = Engine::getComponentRef<C_Health>(*this);
    C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    C_Score* scoreComponent = Engine::getComponentRef<C_Score>(*this);

    if (transformComponent) {
        auto transformData = transformComponent->serializeToVector();
        data.insert(data.end(), transformData.begin(), transformData.end());
    }
    if (healthComponent) {
        auto healthData = healthComponent->serializeToVector();
        data.insert(data.end(), healthData.begin(), healthData.end());
    }
    if (hitboxComponent) {
        auto hitboxData = hitboxComponent->serializeToVector();
        data.insert(data.end(), hitboxData.begin(), hitboxData.end());
    }
    if (scoreComponent) {
        auto scoreData = scoreComponent->serializeToVector();
        data.insert(data.end(), scoreData.begin(), scoreData.end());
    }
    return data;
}

E_Enemy::E_Enemy(int position_x, int position_y, float size_x, float size_y, int type)
{
    addComponent(std::make_shared<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
    addComponent(std::make_shared<C_Health>(20));
    addComponent(std::make_shared<C_Hitbox>(65, 66));
    addComponent(std::make_shared<C_EnemyInfo>(type));
}

void E_Enemy::update()
{
    auto& transform = getComponents()[0];
    auto& health = getComponents()[1];
}

std::string E_Enemy::getType() const {
    return "E_Enemy";
}

std::vector<char> E_Enemy::serializeToVector() {
    std::vector<char> data;
    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    C_Health* healthComponent = Engine::getComponentRef<C_Health>(*this);
    C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    C_EnemyInfo* enemyInfoComponent = Engine::getComponentRef<C_EnemyInfo>(*this);

    if (transformComponent) {
        auto transformData = transformComponent->serializeToVector();
        data.insert(data.end(), transformData.begin(), transformData.end());
    }
    if (healthComponent) {
        auto healthData = healthComponent->serializeToVector();
        data.insert(data.end(), healthData.begin(), healthData.end());
    }
    if (hitboxComponent) {
        auto hitboxData = hitboxComponent->serializeToVector();
        data.insert(data.end(), hitboxData.begin(), hitboxData.end());
    }
    if (enemyInfoComponent) {
        auto enemyInfoData = enemyInfoComponent->serializeToVector();
        data.insert(data.end(), enemyInfoData.begin(), enemyInfoData.end());
    }
    return data;
}
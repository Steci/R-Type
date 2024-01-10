/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.cpp
*/

#include <sstream>
#include <algorithm>
#include "Game.hpp"
#include "Entity.hpp"

E_Bullet::E_Bullet(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y, int idCreator)
{
    addComponent(std::make_shared<C_Transform>(position_x, position_y, size_x, size_y, velocity_x, velocity_y));
    addComponent(std::make_shared<C_Damage>(damage));
    _idCreator = idCreator;
}

std::string E_Bullet::getType() const {
    return "E_Bullet";
}

void E_Bullet::render()
{
    if (IsWindowReady() == true) {
        C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);

        // Check if C_Sprite component exists
        if (this->getComponents().size() > 2) {
            Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;
            Rectangle sourceRec = { 127.0f, 0.0f, transform->_size.x, transform->_size.y};
            printf("SourceRec Infos : %f, %f, %f, %f\n", sourceRec.x, sourceRec.y, sourceRec.width, sourceRec.height);
            printf("Transform Infos : %f, %f, %f, %f\n", transform->_position.x, transform->_position.y, transform->_size.x, transform->_size.y);
            DrawTexturePro(sprite, sourceRec, { transform->_position.x, transform->_position.y, transform->_size.x * 2, transform->_size.y * 2 }, { 0.0f, 0.0f }, 0.0f, WHITE);
        }
    }
}

std::vector<char> E_Bullet::serializeToVector()
{
    std::vector<char> data;

    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    if (transformComponent) {
        auto transformData = transformComponent->serializeToVector();
        data.insert(data.end(), transformData.begin(), transformData.end());
    }

    C_Damage* damageComponent = Engine::getComponentRef<C_Damage>(*this);
    if (damageComponent) {
        auto damageData = damageComponent->serializeToVector();
        data.insert(data.end(), damageData.begin(), damageData.end());
    }

    // C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    // if (hitboxComponent) {
    //     auto hitboxData = hitboxComponent->serializeToVector();
    //     data.insert(data.end(), hitboxData.begin(), hitboxData.end());
    // }
    data.insert(data.end(), reinterpret_cast<const char*>(&_idCreator), reinterpret_cast<const char*>(&_idCreator) + sizeof(_idCreator));
    return data;
}

void E_Bullet::deserializeFromVector(std::vector<char> data) {
    auto it = data.begin();

    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    if (transformComponent) {
        size_t transformSize = sizeof(transformComponent->_position) + sizeof(transformComponent->_size) + sizeof(transformComponent->_velocity);
        std::vector<char> transformData(it, it + transformSize);
        transformComponent->deserializeFromVector(transformData);
        it += transformSize;
    }

    C_Damage* damageComponent = Engine::getComponentRef<C_Damage>(*this);
    if (damageComponent) {
        size_t damageSize = sizeof(damageComponent->_damage);
        std::vector<char> damageData(it, it + damageSize);
        damageComponent->deserializeFromVector(damageData);
        it += damageSize;
    }
    C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    if (hitboxComponent) {
        size_t hitboxSize = sizeof(hitboxComponent->_size) + sizeof(hitboxComponent->_status) + sizeof(hitboxComponent->_time);
        std::vector<char> hitboxData(it, it + hitboxSize);
        hitboxComponent->deserializeFromVector(hitboxData);
        it += hitboxSize;
    }
    std::memcpy(&_idCreator, data.data() + sizeof(C_Transform) + sizeof(C_Damage), sizeof(_idCreator));
}

E_Player::E_Player(int position_x, int position_y, float size_x, float size_y)
{
    addComponent(std::make_shared<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
    addComponent(std::make_shared<C_Health>(100));
    addComponent(std::make_shared<C_Hitbox>(33, 17));
    addComponent(std::make_shared<C_Score>());
}

void E_Player::update()
{
    auto& transform = getComponents()[0];
    auto& health = getComponents()[1];
}

void E_Player::render()
{
    if (IsWindowReady() == true) {
        C_Score *score = Engine::getComponentRef<C_Score>(*this);
        std::string scoreText = "Score: " + std::to_string(score->_score);
        DrawText(scoreText.c_str(), 300, 20, 30, WHITE);
        C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(*this);
        if (hitbox->_status == 1) {
            if ((hitbox->_time % 2) != 0) {
                C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);
                int xPos = transform->_position.x;
                int yPos = transform->_position.y;
                int xSize = transform->_size.x;
                int ySize = transform->_size.y;
                int animation = transform->_animation;
                Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;
                Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
                Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                hitbox->_time -= 1;
            } else {
                hitbox->_time -= 1;
            }
            if (hitbox->_time <= 0) {
                hitbox->_time = 10;
                hitbox->_status = 0;
            }
        } else if (hitbox->_status == 2) {
            C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);
            int xPos = transform->_position.x;
            int yPos = transform->_position.y;
            int xSize = transform->_size.x;
            int ySize = transform->_size.y;
            Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;
            if (transform->_animation <= 7) {
                Rectangle sourceRec = { (float)(xSize * transform->_animation), 0, (float)xSize, (float)ySize };
                Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                transform->_animation += 1;
            }
        } else {
            C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);
            int xPos = transform->_position.x;
            int yPos = transform->_position.y;
            int xSize = transform->_size.x;
            int ySize = transform->_size.y;
            int animation = transform->_animation;
            Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;
            Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
            Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
        }
    }
}

std::vector<char> E_Player::serializeToVector()
{
    printf("Player\n");
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

std::string E_Player::getType() const {
    return "E_Player";
}

void E_Player::deserializeFromVector(std::vector<char> data) {
        auto it = data.begin();

    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    if (transformComponent) {
        size_t transformSize = sizeof(transformComponent->_position) + sizeof(transformComponent->_size) + sizeof(transformComponent->_velocity )+ sizeof(transformComponent->_animation);
        std::vector<char> transformData(it, it + transformSize);
        transformComponent->deserializeFromVector(transformData);
        it += transformSize;
    }

    C_Health* healthComponent = Engine::getComponentRef<C_Health>(*this);
    if (healthComponent) {
        size_t healthSize = sizeof(healthComponent->_health);
        std::vector<char> healthData(it, it + healthSize);
        healthComponent->deserializeFromVector(healthData);
        it += healthSize;
    }

    C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    if (hitboxComponent) {
        size_t hitboxSize = sizeof(hitboxComponent->_size) + sizeof(hitboxComponent->_status) + sizeof(hitboxComponent->_time);
        std::vector<char> hitboxData(it, it + hitboxSize);
        hitboxComponent->deserializeFromVector(hitboxData);
        it += hitboxSize;
    }

    C_Score* scoreComponent = Engine::getComponentRef<C_Score>(*this);
    if (scoreComponent) {
        size_t scoreSize = sizeof(scoreComponent->_score);
        std::vector<char> scoreData(it, it + scoreSize);
        scoreComponent->deserializeFromVector(scoreData);
        it += scoreSize;
    }
}

E_Enemy::E_Enemy(int position_x, int position_y, float size_x, float size_y, int type)
{
    addComponent(std::make_shared<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
    addComponent(std::make_shared<C_Health>(20));
    addComponent(std::make_shared<C_Hitbox>(65, 66));
    addComponent(std::make_shared<C_EnemyInfo>(type));
    addComponent(std::make_shared<C_AnimationInfo>(65, 66, 7, 0, 8));
}

void E_Enemy::update()
{
    auto& transform = getComponents()[0];
    auto& health = getComponents()[1];
}

void E_Enemy::render()
{
    if (IsWindowReady() == true) {
        C_Hitbox *hitbox = Engine::getComponentRef<C_Hitbox>(*this);
        if (hitbox->_status == 1) {
            if ((hitbox->_time % 2) != 0) {
                C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);
                int xPos = transform->_position.x;
                int yPos = transform->_position.y;
                int xSize = transform->_size.x;
                int ySize = transform->_size.y;
                int animation = transform->_animation;
                Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;
                Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
                Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                hitbox->_time -= 1;
            } else {
                hitbox->_time -= 1;
            }
            if (hitbox->_time <= 0) {
                hitbox->_time = 10;
                hitbox->_status = 0;
            }
        } else if (hitbox->_status == 2) {
            C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);
            int xPos = transform->_position.x;
            int yPos = transform->_position.y;
            int xSize = transform->_size.x;
            int ySize = transform->_size.y;
            Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;
            if (transform->_animation <= 7) {
                Rectangle sourceRec = { (float)(xSize * transform->_animation), 0, (float)xSize, (float)ySize };
                Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                transform->_animation += 1;
            }
        } else {
            C_Transform *transform = Engine::getComponentRef<C_Transform>(*this);
            C_AnimationInfo *animationInfo = Engine::getComponentRef<C_AnimationInfo>(*this);
            Texture2D sprite = Engine::getComponentRef<C_Sprite>(*this)->_texture;

            int xPos = transform->_position.x;
            int yPos = transform->_position.y;
            int xSize = transform->_size.x;
            int ySize = transform->_size.y;

            int maxXframe = animationInfo->_maxXframe;
            int maxYframe = animationInfo->_maxYframe;

            Rectangle frameRec = { 0.0f, 0.0f, (float)xSize, (float)ySize };

            // animationInfo->_framesCounter++;
            // printf("Speed = %d\n", animationInfo->_speed);
            // printf("60/speed = %d\n", (60 / animationInfo->_speed));
            // printf("animationInfo->_framesCounter = %d\n", animationInfo->_framesCounter);
            // if (animationInfo->_framesCounter >= (60 / animationInfo->_speed)) {
            //     printf("animationInfo->_framesCounter = %d\n", animationInfo->_framesCounter);
            //     animationInfo->_framesCounter = 0;
            //     animationInfo->_currentFrame++;

            //     printf("animationInfo->_currentFrame = %d\n", animationInfo->_currentFrame);
            //     if (animationInfo->_currentFrame > maxXframe) {
            //         animationInfo->_currentFrame = 0;
            //     }
            //     frameRec.x = (float)animationInfo->_currentFrame * (float)xSize;
            //     printf("frameRec.x = %f\n", frameRec.x);
            // }
            DrawTextureRec(sprite, frameRec, {(float)xPos, (float)yPos }, WHITE);
        }
    }
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

void E_Enemy::deserializeFromVector(std::vector<char> data) {
    auto it = data.begin();

    C_Transform* transformComponent = Engine::getComponentRef<C_Transform>(*this);
    if (transformComponent) {
        size_t transformSize = sizeof(transformComponent->_position) + sizeof(transformComponent->_size) + sizeof(transformComponent->_velocity) + sizeof(transformComponent->_animation);
        std::vector<char> transformData(it, it + transformSize);
        transformComponent->deserializeFromVector(transformData);
        it += transformSize;
    }

    C_Health* healthComponent = Engine::getComponentRef<C_Health>(*this);
    if (healthComponent) {
        size_t healthSize = sizeof(healthComponent->_health);
        std::vector<char> healthData(it, it + healthSize);
        healthComponent->deserializeFromVector(healthData);
        it += healthSize;
    }

    C_Hitbox* hitboxComponent = Engine::getComponentRef<C_Hitbox>(*this);
    if (hitboxComponent) {
        size_t hitboxSize = sizeof(hitboxComponent->_size) + sizeof(hitboxComponent->_time) + sizeof(hitboxComponent->_status);
        std::vector<char> hitboxData(it, it + hitboxSize);
        hitboxComponent->deserializeFromVector(hitboxData);
        it += hitboxSize;
    }

    C_EnemyInfo* enemyInfoComponent = Engine::getComponentRef<C_EnemyInfo>(*this);
    if (enemyInfoComponent) {
        size_t enemyInfoSize = sizeof(enemyInfoComponent->_type);
        std::vector<char> enemyInfoData(it, it + enemyInfoSize);
        enemyInfoComponent->deserializeFromVector(enemyInfoData);
        it += enemyInfoSize;
    }
}
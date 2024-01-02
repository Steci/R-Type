/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.cpp
*/

#include "../include/Engine.hpp"

E_Bullet::E_Bullet(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y)
{
    addComponent(std::make_unique<C_Transform>(position_x, position_y, size_x, size_y, velocity_x, velocity_y));
    addComponent(std::make_unique<C_Sprite>(path));
    addComponent(std::make_unique<C_Damage>(name, damage));
}

void E_Bullet::render()
{
    auto* transform = dynamic_cast<C_Transform*>(getComponents()[0].get());
    auto* spriteComponent = dynamic_cast<C_Sprite*>(getComponents()[1].get());
    if (transform && spriteComponent) {
        transform->_position.x += transform->_velocity.x;
        transform->_position.y += transform->_velocity.y;
        Texture2D sprite = spriteComponent->_texture;
        Rectangle sourceRec = { 0.0f, 0.0f, (float)transform->_size.x, (float)transform->_size.y };
        Rectangle destRec = { (float)transform->_position.x, (float)transform->_position.y, (float)transform->_size.x * 2, (float)transform->_size.y * 2 };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
    } 
}

E_Player::E_Player(std::string path, int position_x, int position_y, float size_x, float size_y)
{
    addComponent(std::make_unique<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
    addComponent(std::make_unique<C_Health>(100));
    addComponent(std::make_unique<C_Sprite>(path));
    addComponent(std::make_unique<C_Hitbox>(33, 17));
    addComponent(std::make_unique<C_Score>());
}

void E_Player::update()
{
    auto& transform = getComponents()[0];
    auto& health = getComponents()[1];
}

void E_Player::render()
{
    C_Score *score = dynamic_cast<C_Score*>(getComponents()[4].get());
    std::string scoreText = "Score: " + std::to_string(score->_score);
    DrawText(scoreText.c_str(), 250, 250, 30, WHITE);
    C_Hitbox *hitbox = dynamic_cast<C_Hitbox*>(getComponents()[3].get());
    if (hitbox->_status == 1) {
        if ((hitbox->_time % 2) != 0) {
            int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
            int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
            int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
            int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
            int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
            Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
            Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
            Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
            for (auto& bullet : _bullets) {
                bullet->render();
            }
            hitbox->_time -= 1;
        } else {
            hitbox->_time -= 1;
        }
        if (hitbox->_time <= 0) {
            hitbox->_time = 10;
            hitbox->_status = 0;
        }
    } else if (hitbox->_status == 2) {
        int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
        int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
        int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
        int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
        Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
        C_Transform *transform = dynamic_cast<C_Transform*>(getComponents()[0].get());
        if (transform->_animation <= 7) {
            Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
            Rectangle sourceRec = { (float)(xSize * transform->_animation), 0, (float)xSize, (float)ySize };
            Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
            transform->_animation += 1;
        }
        for (auto& bullet : _bullets) {
            bullet->render();
        }
    } else {
        int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
        int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
        int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
        int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
        int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
        Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
        Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
        Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
        for (auto& bullet : _bullets) {
            bullet->render();
        } 
    }
}

void E_Player::newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y)
{
    auto newBullet = std::make_unique<E_Bullet>(path, name, damage, position_x, position_y, size_x, size_y, velocity_x, velocity_y);
    _bullets.push_back(std::move(newBullet));
}

E_Enemy::E_Enemy(std::string path, int position_x, int position_y, float size_x, float size_y)
{
    addComponent(std::make_unique<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
    addComponent(std::make_unique<C_Health>(20));
    addComponent(std::make_unique<C_Sprite>(path));
    addComponent(std::make_unique<C_Hitbox>(65, 66));
}

void E_Enemy::update()
{
    auto& transform = getComponents()[0];
    auto& health = getComponents()[1];
}

void E_Enemy::render()
{
    C_Hitbox *hitbox = dynamic_cast<C_Hitbox*>(getComponents()[3].get());
    if (hitbox->_status == 1) {
        if ((hitbox->_time % 2) != 0) {
            int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
            int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
            int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
            int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
            int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
            Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
            Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
            Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
            for (auto& bullet : _bullets) {
                bullet->render();
            }
            hitbox->_time -= 1;
        } else {
            hitbox->_time -= 1;
        }
        if (hitbox->_time <= 0) {
            hitbox->_time = 10;
            hitbox->_status = 0;
        }
    } else if (hitbox->_status == 2) {
        int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
        int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
        int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
        int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
        Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
        C_Transform *transform = dynamic_cast<C_Transform*>(getComponents()[0].get());
        if (transform->_animation <= 7) {
            Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
            Rectangle sourceRec = { (float)(xSize * transform->_animation), 0, (float)xSize, (float)ySize };
            Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
            transform->_animation += 1;
        }
        for (auto& bullet : _bullets) {
            bullet->render();
        }
    } else {
        int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
        int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
        int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
        int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
        int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
        Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
        Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
        Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
        for (auto& bullet : _bullets) {
            bullet->render();
        } 
    }
}

void E_Enemy::newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y)
{
    auto newBullet = std::make_unique<E_Bullet>(path, name, damage, position_x, position_y, size_x, size_y, velocity_x, velocity_y);
    _bullets.push_back(std::move(newBullet));
}

namespace Engine {
    C_Transform* getTransform(std::unique_ptr<IEntity> entity)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity->getComponentOfType(typeid(C_Transform)));
        if (transform) {
            return (transform);
        }
        return (nullptr);
    }

    C_Damage* getDamage(std::unique_ptr<IEntity> entity)
    {
        C_Damage* damage = dynamic_cast<C_Damage*>(entity->getComponentOfType(typeid(C_Damage)));
        if (damage) {
            return (damage);
        }
        return (nullptr);
    }

    C_Health* getHealth(std::unique_ptr<IEntity> entity)
    {
        C_Health* health = dynamic_cast<C_Health*>(entity->getComponentOfType(typeid(C_Health)));
        if (health) {
            return (health);
        }
        return (nullptr);
    }

    C_Sprite* getSprite(std::unique_ptr<IEntity> entity)
    {
        C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity->getComponentOfType(typeid(C_Sprite)));
        if (sprite) {
            return (sprite);
        }
        return (nullptr);
    }

    C_Hitbox* getHitbox(std::unique_ptr<IEntity> entity)
    {
        C_Hitbox* hitbox = dynamic_cast<C_Hitbox*>(entity->getComponentOfType(typeid(C_Hitbox)));
        if (hitbox) {
            return (hitbox);
        }
        return (nullptr);
    }

    // Set Components

    void setTransformPos(IEntity& entity, Vec2 newPos)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity.getComponentOfType(typeid(C_Transform)));
        if (transform) {
            transform->_position = newPos;
        }
    };

    void setTransformSize(IEntity& entity, Vec2 newSize)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity.getComponentOfType(typeid(C_Transform)));
        if (transform) {
            transform->_size = newSize;
        }
    };

    void setTransformVel(IEntity& entity, Vec2 newVel)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity.getComponentOfType(typeid(C_Transform)));
        if (transform) {
            transform->_velocity = newVel;
        }
    };

    void setTransformAni(IEntity& entity, int newAni)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity.getComponentOfType(typeid(C_Transform)));
        if (transform) {
            transform->_animation = newAni;
        }
    };

    void setDamageName(IEntity& entity, std::string newName)
    {
        C_Damage* damage = dynamic_cast<C_Damage*>(entity.getComponentOfType(typeid(C_Damage)));
        if (damage) {
            damage->_name = newName;
        }
    }

    void setDamageDamage(IEntity& entity, int newDamage)
    {
        C_Damage* damage = dynamic_cast<C_Damage*>(entity.getComponentOfType(typeid(C_Damage)));
        if (damage) {
            damage->_damage = newDamage;
        }
    }

    void setHealth(IEntity& entity, int newHealth)
    {
        C_Health* health = dynamic_cast<C_Health*>(entity.getComponentOfType(typeid(C_Health)));
        if (health) {
            health->_health = newHealth;
        }
    }

    void setSpriteName(IEntity& entity, std::string newSpriteName)
    {
        C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity.getComponentOfType(typeid(C_Sprite)));
        if (sprite) {
            sprite->_name = newSpriteName;
        }
    }

    void setSpriteImage(IEntity& entity, Image newImage)
    {
        C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity.getComponentOfType(typeid(C_Sprite)));
        if (sprite) {
            sprite->_image = newImage;
        }
    }

    void setSpriteTexture(IEntity& entity, Texture2D newTexture)
    {
        C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity.getComponentOfType(typeid(C_Sprite)));
        if (sprite) {
            sprite->_texture = newTexture;
        }
    }

    void setHitboxSize(IEntity& entity, Vec2 newHitbox)
    {
        C_Hitbox* hitbox = dynamic_cast<C_Hitbox*>(entity.getComponentOfType(typeid(C_Hitbox)));
        if (hitbox) {
            hitbox->_size = newHitbox;
        }
    }

    void setHitboxTime(IEntity& entity, int newTime)
    {
        C_Hitbox* hitbox = dynamic_cast<C_Hitbox*>(entity.getComponentOfType(typeid(C_Hitbox)));
        if (hitbox) {
            hitbox->_time = newTime;
        }
    }

    void setHitboxStatus(IEntity& entity, int newStatus)
    {
        C_Hitbox* hitbox = dynamic_cast<C_Hitbox*>(entity.getComponentOfType(typeid(C_Hitbox)));
        if (hitbox) {
            hitbox->_status = newStatus;
        }
    }

    void setScore(IEntity& entity, int newScore)
    {
        C_Score* score = dynamic_cast<C_Score*>(entity.getComponentOfType(typeid(C_Score)));
        if (score) {
            score->_score = newScore;
        }
    }
};
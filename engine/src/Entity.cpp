/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.cpp
*/

#include "../include/Engine.hpp"

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
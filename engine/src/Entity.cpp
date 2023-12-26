/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.cpp
*/

#include "Engine.hpp"

namespace Engine {

    C_Transform* getTransform(std::unique_ptr<IEntity> entity)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity->getComponentOfType(typeid(C_Transform)));
        if (transform) {
            return (transform);
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

    void setTransformPos (IEntity& entity, Vec2 newTransform)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity.getComponentOfType(typeid(C_Transform)));
        if (transform) {
            transform->_position = newTransform;
        }
    };

    void setTransformRot (IEntity& entity, Vec2 newTransform)
    {
        C_Transform* transform = dynamic_cast<C_Transform*>(entity.getComponentOfType(typeid(C_Transform)));
        if (transform) {
            transform->_rotation = newTransform;
        }
    };

    void setHealth (IEntity& entity, int newHealth)
    {
        C_Health* health = dynamic_cast<C_Health*>(entity.getComponentOfType(typeid(C_Health)));
        if (health) {
            health->_health = newHealth;
        }
    }

    void setSpriteName (IEntity& entity, std::string newSpriteName)
    {
        C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity.getComponentOfType(typeid(C_Sprite)));
        if (sprite) {
            sprite->_name = newSpriteName;
        }
    }

    void setSprite(IEntity& entity, Texture2D newTexture)
    {
        C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity.getComponentOfType(typeid(C_Sprite)));
        if (sprite) {
            sprite->_texture = newTexture;
        }
    }

    void setHitbox (IEntity& entity, Vec2 newHitbox)
    {
        C_Hitbox* hitbox = dynamic_cast<C_Hitbox*>(entity.getComponentOfType(typeid(C_Hitbox)));
        if (hitbox) {
            hitbox->_size = newHitbox;
        }
    }
};
/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include "Engine.hpp"

// Get Components
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

void setSprite (IEntity& entity, Texture2D newSprite)
{
    C_Sprite* sprite = dynamic_cast<C_Sprite*>(entity.getComponentOfType(typeid(C_Sprite)));
    if (sprite) {
        sprite->_sprite = newSprite;
    }
}

void setHitbox (IEntity& entity, Vec2 newHitbox)
{
    C_Hitbox* hitbox = dynamic_cast<C_Hitbox*>(entity.getComponentOfType(typeid(C_Hitbox)));
    if (hitbox) {
        hitbox->_size = newHitbox;
    }
}

// Get Component Reference with template
template<typename T>
T* getComponentRef(IEntity& entity)
{
    T* component = dynamic_cast<T*>(entity.getComponentOfType(typeid(T)));
    if (component) {
        return (component);
    }
    return (nullptr);
}

int main(void)
{
    SystemManager manager;

    manager.addSystem<S_Renderer>(800, 600, 60, "Game");

    IEntity *enemy = new E_Enemy("assets/placeholder.png");
    IEntity *player =   new E_Player();

    // Add the entity to the system
    manager.getSystem<S_Renderer>()->addEntity(enemy);
    manager.getSystem<S_Renderer>()->addEntity(player);

    // Modify the entity's components
    C_Transform* transform = getComponentRef<C_Transform>(*player);
    transform->_position = {200, 200};

    while (1) {
        if(IsKeyDown(KEY_RIGHT)) {
            transform->_position.x += 3;
        }
        if (IsKeyDown(KEY_LEFT)) {
            transform->_position.x -= 3;
        }
        if (IsKeyDown(KEY_UP)) {
            transform->_position.y -= 3;
        }
        if (IsKeyDown(KEY_DOWN)) {
            transform->_position.y += 3;
        }
        manager.update();
    };

    return 0;
}
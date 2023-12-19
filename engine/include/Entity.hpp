/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include "Component.hpp"

/**
 * @brief The IEntity class represents an entity in the game engine.
 *
 * This class defines the interface for all entities in the game engine.
 * An entity is an object that can be updated and rendered in the game.
 * It can have multiple components attached to it.
 */
class IEntity {
    public:
        virtual ~IEntity() = default;

        /**
         * @brief Updates the entity.
         *
         * This method is called every frame to update the state of the entity.
         */
        virtual void update() = 0;

        /**
         * @brief Renders the entity.
         *
         * This method is called every frame to render the entity on the screen.
         */
        virtual void render() = 0;

        /**
         * @brief Adds a component to the entity.
         *
         * @param component The component to add.
         */
        virtual void addComponent(std::unique_ptr<Component> component) = 0;

        /**
         * @brief Removes a component from the entity.
         *
         * @param component The component to remove.
         */
        virtual void removeComponent(Component* component) = 0;

        /**
         * @brief Gets the list of components attached to the entity.
         *
         * @return A reference to the vector of components.
         */
        virtual std::vector<std::unique_ptr<Component>>& getComponents() = 0;

        /**
         * @brief Gets a component of a specific type attached to the entity.
         *
         * @param ti The type information of the component.
         * @return A pointer to the component if found, nullptr otherwise.
         */
        virtual Component* getComponentOfType(const std::type_info& ti) = 0;
};

class AbstractEntity : public IEntity {
    public:
        void update() override = 0;
        void render() override = 0;
        void addComponent(std::unique_ptr<Component> component) override {
            components.push_back(std::move(component));
        }
        void removeComponent(Component* component) override {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (it->get() == component) {
                    components.erase(it);
                    return;
                }
            }
        }
        std::vector<std::unique_ptr<Component>>& getComponents() override {
            return components;
        }
        Component* getComponentOfType(const std::type_info& ti) override {
            for (auto& component : components) {
                if (typeid(*component) == ti) {
                    return component.get();
                }
            }
            return nullptr;
        }
    private:
        std::vector<std::unique_ptr<Component>> components;
};

class E_Player : public AbstractEntity {
    public:
        E_Player() {
            C_Transform transform;
            C_Health health;
            C_Sprite sprite;
            C_Hitbox hitbox;
            hitbox._size = {50, 50};
            addComponent(std::make_unique<C_Transform>(transform));
            addComponent(std::make_unique<C_Health>(health));
            addComponent(std::make_unique<C_Sprite>(sprite));
            addComponent(std::make_unique<C_Hitbox>(hitbox));
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
        }
        void render() override {
            int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
            int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
            int squareSize = 50;
            DrawRectangle(xPos, yPos, squareSize, squareSize, BLUE);
        }
};

class E_Enemy : public AbstractEntity {
    public:
        E_Enemy(std::string path) {
            C_Transform transform;
            C_Health health;
            C_Sprite sprite;
            C_Hitbox hitbox;
            hitbox._size = {50, 50};
            sprite._sprite = LoadTexture(path.c_str());
            addComponent(std::make_unique<C_Transform>(transform));
            addComponent(std::make_unique<C_Health>(health));
            addComponent(std::make_unique<C_Sprite>(sprite));
            addComponent(std::make_unique<C_Hitbox>(hitbox));
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
        }
        void render() override {
            auto& transform = getComponents()[0];
            int xPos = dynamic_cast<C_Transform*>(transform.get())->_position.x;
            int yPos = dynamic_cast<C_Transform*>(transform.get())->_position.y;
            int squareSize = 50;
            DrawRectangle(xPos, yPos, squareSize, squareSize, RED);
        }
};

// Get Components
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
};
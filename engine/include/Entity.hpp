/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

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
        virtual void addComponent(std::shared_ptr<Component> component) = 0;

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
        virtual std::vector<std::shared_ptr<Component>>& getComponents() = 0;

        /**
         * @brief Gets a component of a specific type attached to the entity.
         *
         * @param ti The type information of the component.
         * @return A pointer to the component if found, nullptr otherwise.
         */
        virtual Component* getComponentOfType(const std::type_info& ti) = 0;

        virtual std::vector<char> serializeToVector() = 0;
        virtual void deserializeFromVector(std::vector<char> data) = 0;
};

class Entity : public IEntity {
    public:
        void update() override = 0;
        void render() override = 0;
        std::vector<char> serializeToVector() override = 0;
        void deserializeFromVector(std::vector<char> data) override = 0;

        void addComponent(std::shared_ptr<Component> component) override {
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
        std::vector<std::shared_ptr<Component>>& getComponents() override {
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
        std::vector<std::shared_ptr<Component>> components;
};

namespace Engine {
    C_Transform* getTransform(std::shared_ptr<IEntity> entity);
    C_Damage* getDamage(std::shared_ptr<IEntity> entity);
    C_Health* getHealth(std::shared_ptr<IEntity> entity);
    C_Sprite* getSprite(std::shared_ptr<IEntity> entity);
    C_Hitbox* getHitbox(std::shared_ptr<IEntity> entity);
    C_Score* getScore(std::shared_ptr<IEntity> entity);
    C_EnemyInfo* getEnemyInfo(std::shared_ptr<IEntity> entity);
    void setTransformPos(IEntity& entity, Vec2 newPos);
    void setTransformSize(IEntity& entity, Vec2 newSize);
    void setTransformVel(IEntity& entity, Vec2 newVel);
    void setTransformAni(IEntity& entity, int newAni);
    void setDamageDamage(IEntity& entity, int newDamage);
    void setHealth(IEntity& entity, int newHealth);
    void setSpriteName(IEntity& entity, std::string newSpriteName);
    void setSpriteImage(IEntity& entity, Image newImage);
    void setSpriteTexture(IEntity& entity, Texture2D newTexture);
    void setHitboxSize(IEntity& entity, Vec2 newHitbox);
    void setHitboxTime(IEntity& entity, int newTime);
    void setHitboxStatus(IEntity& entity, int newStatus);
    void setScore(IEntity& entity, int newScore);
    void setEnemyInfoType(IEntity& entity, int newType);

    template<typename T>
    T* getComponentRef(IEntity& entity)
    {
        T* component = dynamic_cast<T*>(entity.getComponentOfType(typeid(T)));
        if (component) {
            return (component);
        }
        return (nullptr);
    }
    //template<typename T>
    //const T* getComponentRef(const IEntity& entity) {
    //    T* component = dynamic_cast<const T*>(entity.getComponentOfType(typeid(T)));
    //    if (component) {
    //        return (component);
    //    }
    //    return (nullptr);
    //}
}
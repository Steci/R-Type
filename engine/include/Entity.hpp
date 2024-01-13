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

        virtual std::string getType() const = 0;

        virtual std::vector<char> serializeToVector() = 0;
        virtual void deserializeFromVector(std::vector<char> data) = 0;
        virtual void setId(int id) = 0;
        virtual int getId() const = 0;
};

class Entity : public IEntity {
    public:
        void update() override = 0;
        void render() override {};
        std::vector<char> serializeToVector() override {};
        std::string getType() const override = 0;
        void deserializeFromVector(std::vector<char> data) override {};

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
        void setId(int id) {
            _id = id;
        }
        int getId() const {
            return _id;
        }

    private:
        int _id;
        std::vector<std::shared_ptr<Component>> components;
};

namespace Engine {
    /**
     * @brief Return C_transform component of a specific entity.
     *
     * @param entity The entity where we want to retrieve the information.
     * @return A pointer to the C_Transform component.
     */
    C_Transform* getTransform(std::shared_ptr<IEntity> entity);

    /**
     * @brief Return C_Damage component of a specific entity.
     *
     * @param entity The entity where we want to retrieve the information.
     * @return A pointer to the C_Damage component.
     */
    C_Damage* getDamage(std::shared_ptr<IEntity> entity);

    /**
     * @brief Return C_Health component of a specific entity.
     *
     * @param entity The entity where we want to retrieve the information.
     * @return A pointer to the C_Health component.
     */
    C_Health* getHealth(std::shared_ptr<IEntity> entity);

    /**
     * @brief Return C_Sprite component of a specific entity.
     *
     * @param entity The entity where we want to retrieve the information.
     * @return A pointer to the C_Sprite component.
     */
    C_Sprite* getSprite(std::shared_ptr<IEntity> entity);

    /**
     * @brief Return C_Hitbox component of a specific entity.
     *
     * @param entity The entity where we want to retrieve the information.
     * @return A pointer to the C_Hitbox component.
     */
    C_Hitbox* getHitbox(std::shared_ptr<IEntity> entity);

    /**
     * @brief Return C_Score component of a specific entity.
     *
     * @param entity The entity where we want to retrieve the information.
     * @return A pointer to the C_Score component.
     */
    C_Score* getScore(std::shared_ptr<IEntity> entity);

    C_EnemyInfo* getEnemyInfo(std::shared_ptr<IEntity> entity);
    /**
     * @brief Setup the new position on the C_transform component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newPos The newPos is the new Vector2 Position for the C_transform component of the specific adress entity
     */
    void setTransformPos(IEntity& entity, Vec2 newPos);

    /**
     * @brief Setup the new size on the C_transform component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newSize The newSize is the new Vector2 size for the C_transform component of the specific adress entity
     */
    void setTransformSize(IEntity& entity, Vec2 newSize);

    /**
     * @brief Setup the new velocity on the C_transform component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newVel The newVel is the new Vector2 velocity for the C_transform component of the specific adress entity
     */
    void setTransformVel(IEntity& entity, Vec2 newVel);

    /**
     * @brief Setup the new aniamtion on the C_transform component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newAni The newAni is the new animation for the C_transform component of the specific adress entity
     */
    void setTransformAni(IEntity& entity, int newAni);

    /**
     * @brief Setup the new damage on the C_Damage component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newDamage The newDamage is the new damage for the C_Damage component of the specific adress entity
     */
    void setDamageDamage(IEntity& entity, int newDamage);

    /**
     * @brief Setup the new health on the C_Health component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newHealth The newHealth is the new health for the C_Health component of the specific adress entity
     */
    void setHealth(IEntity& entity, int newHealth);

    /**
     * @brief Setup the new asset path on the C_Sprite component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newSpriteName The newSpriteName is the new asset path for the C_Sprite component of the specific adress entity
     */
    void setSpriteName(IEntity& entity, std::string newSpriteName);

    /**
     * @brief Setup the new Image on the C_Sprite component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newImage The newImage is the new Image for the C_Sprite component of the specific adress entity
     */
    void setSpriteImage(IEntity& entity, Image newImage);

    /**
     * @brief Setup the new Texture on the C_Sprite component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newTexture The newTexture is the new Texture for the C_Sprite component of the specific adress entity
     */
    void setSpriteTexture(IEntity& entity, Texture2D newTexture);

    /**
     * @brief Setup the new check collision box on the C_Hitbox component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newHitbox The newHitbox is the new check collision box for the C_Hitbox component of the specific adress entity
     */
    void setHitboxSize(IEntity& entity, Vec2 newHitbox);

    /**
     * @brief Setup the new time for the animtaion damage on the C_Hitbox component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newTime The newTime is the new time for the animtaion damage for the C_Hitbox component of the specific adress entity
     */
    void setHitboxTime(IEntity& entity, int newTime);

    /**
     * @brief Setup the new status on the C_Hitbox component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newStatus The newStatus is the new status for the C_Hitbox component of the specific adress entity
     */
    void setHitboxStatus(IEntity& entity, int newStatus);

    /**
     * @brief Setup the new player score on the C_Score component of the specific adress entity.
     *
     * @param entity The adress entity where we want to setup the new informations.
     * @param newScore The newStatus is the new player score for the C_Score component of the specific adress entity
     */
    void setScore(IEntity& entity, int newScore);
    void setEnemyInfoType(IEntity& entity, int newType);

    template<typename T>
    /**
     * @brief Depending on the address of an entity given as a parameter. It will search if the existing component exists in the function. If yes, it casts it and returns it as a pointer, otherwise it returns nullptr.
     *
     * @param entity The entity allows you to know on which entity to look for the component in question.
     * @return A pointer to the component if found, nullptr otherwise.
     */
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
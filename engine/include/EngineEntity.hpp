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
        /**
         * @brief Destructor for the IEntity class.
         */
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

        /**
         * @brief Gets the type of the entity.
         *
         * @return The type of the entity as a string.
         */
        virtual std::string getType() const = 0;

        /**
         * @brief Serializes the entity to a vector of characters.
         *
         * @return The serialized entity as a vector of characters.
         */
        virtual std::vector<char> serializeToVector() = 0;

        /**
         * @brief Deserializes the entity from a vector of characters.
         *
         * @param data The vector of characters containing the serialized entity.
         */
        virtual void deserializeFromVector(std::vector<char> data) = 0;

        /**
         * @brief Sets the ID of the entity.
         *
         * @param id The ID to set.
         */
        virtual void setId(int id) = 0;

        /**
         * @brief Gets the ID of the entity.
         *
         * @return The ID of the entity.
         */
        virtual int getId() const = 0;

        /**
         * @brief Sets the server ID of the entity.
         *
         * @param id The server ID to set.
         */
        virtual void setIdServer(int id) = 0;

        /**
         * @brief Gets the server ID of the entity.
         *
         * @return The server ID of the entity.
         */
        virtual int getIdServer() const = 0;
};

/**
 * @brief The Entity class represents an entity in the game.
 *
 * This class is an abstract base class that provides common functionality for game entities.
 * It defines pure virtual functions for updating, rendering, serializing, deserializing, and getting the type of the entity.
 * It also provides functions for adding and removing components, getting the components, and getting/setting the entity's ID.
 */
/**
 * @brief The Entity class represents a game entity.
 *
 * This class is an abstract base class that defines the common interface and functionality for all game entities.
 * It provides methods for updating, rendering, serializing, deserializing, and managing components of an entity.
 * Each entity has a unique ID and an ID assigned by the server.
 */
class Entity : public IEntity {
    public:
        /**
         * @brief Updates the entity.
         *
         * This pure virtual function is called to update the state of the entity.
         * Subclasses must implement this function to define the specific behavior of the entity during an update.
         */
        void update() override = 0;

        /**
         * @brief Renders the entity.
         *
         * This function is called to render the entity.
         * Subclasses can override this function to define the specific rendering behavior of the entity.
         */
        void render() override {};

        /**
         * @brief Serializes the entity to a vector of characters.
         *
         * This function is called to serialize the entity into a vector of characters.
         * Subclasses can override this function to define the specific serialization behavior of the entity.
         *
         * @return The serialized entity as a vector of characters.
         */
        std::vector<char> serializeToVector() override {return std::vector<char>();};

        /**
         * @brief Returns the type of the entity.
         *
         * This pure virtual function is called to get the type of the entity.
         * Subclasses must implement this function to return the specific type of the entity.
         *
         * @return The type of the entity as a string.
         */
        std::string getType() const override = 0;

        /**
         * @brief Deserializes the entity from a vector of characters.
         *
         * This function is called to deserialize the entity from a vector of characters.
         * Subclasses can override this function to define the specific deserialization behavior of the entity.
         *
         * @param data The vector of characters containing the serialized entity.
         */
        void deserializeFromVector(std::vector<char> data) override {};

        /**
         * @brief Adds a component to the entity.
         *
         * This function is called to add a component to the entity.
         * The component is moved into the entity's list of components.
         *
         * @param component The component to add.
         */
        void addComponent(std::shared_ptr<Component> component) override {
            components.push_back(std::move(component));
        }

        /**
         * @brief Removes a component from the entity.
         *
         * This function is called to remove a component from the entity.
         * The component is searched for in the entity's list of components and removed if found.
         *
         * @param component The component to remove.
         */
        void removeComponent(Component* component) override {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (it->get() == component) {
                    components.erase(it);
                    return;
                }
            }
        }

        /**
         * @brief Returns the list of components of the entity.
         *
         * This function is called to get the list of components of the entity.
         *
         * @return The list of components of the entity.
         */
        std::vector<std::shared_ptr<Component>>& getComponents() override {
            return components;
        }

        /**
         * @brief Returns a component of the specified type.
         *
         * This function is called to get a component of the specified type from the entity.
         * The type is compared using the typeid operator.
         *
         * @param ti The type_info object representing the type of the component.
         * @return A pointer to the component of the specified type, or nullptr if not found.
         */
        Component* getComponentOfType(const std::type_info& ti) override {
            for (auto& component : components) {
                if (typeid(*component) == ti) {
                    return component.get();
                }
            }
            return nullptr;
        }

        /**
         * @brief Sets the ID of the entity.
         *
         * This function is called to set the ID of the entity.
         *
         * @param id The ID to set.
         */
        void setId(int id) {
            _id = id;
        }

        /**
         * @brief Returns the ID of the entity.
         *
         * This function is called to get the ID of the entity.
         *
         * @return The ID of the entity.
         */
        int getId() const {
            return _id;
        }

        /**
         * @brief Sets the server ID of the entity.
         *
         * This function is called to set the server ID of the entity.
         *
         * @param id The server ID to set.
         */
        void setIdServer(int id) {
            _idServer = id;
        }

        /**
         * @brief Returns the server ID of the entity.
         *
         * This function is called to get the server ID of the entity.
         *
         * @return The server ID of the entity.
         */
        int getIdServer() const {
            return _idServer;
        }

    private:
        int _id; // The ID of the entity
        int _idServer; // The ID assigned by the server
        std::vector<std::shared_ptr<Component>> components; // The list of components of the entity
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
        auto tmp = entity.getComponentOfType(typeid(T));
        if (tmp == nullptr)
            return nullptr;

        T* component = dynamic_cast<T*>(tmp);
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

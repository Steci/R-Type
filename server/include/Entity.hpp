/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include "Engine.hpp"
#include "EngineSystem.hpp"

/**
 * @brief The E_Bullet class is the bullet entity.
 */
class E_Bullet : public Entity {
    public:
        /**
         * @brief the constructor of the class E_Bullet with params
         *
         * During this constructor the different components that make up the entity will be created
         *
         * @param damage The damage is the bullet damage.
         * @param position_x The position_x is the bullet position on the x axis.
         * @param position_y The position_y is the bullet position on the y axis.
         * @param size_x The size_x is the bullet size on the x axis of the entity.
         * @param size_y The size_y is the bullet size on the y axis of the entity.
         * @param velocity_x The velocity_x is the bullet velocity on the x axis of the entity.
         * @param velocity_y The velocity_y is the bullet velocity on the y axis of the entity.
         * @param idCreator The idCreator is this int allows you to know who created this bullet.
         */
        E_Bullet(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y, int idCreator);
        
        /**
         * @brief Construct a new e bullet object
         * 
         */
        E_Bullet() = default;

        /**
         * @brief is the update of the bullet
         * 
         */
        void update() override {};

        /**
         * @brief Get the Type object
         * 
         * @return std::string is the type of the entity
         */
        std::string getType() const override;

        /**
         * @brief serialize the entity to a vector
         * 
         * @return std::vector<char> is the vector of the entity
         */
        std::vector<char> serializeToVector() override;

        /**
         * @brief Get the Id Creator object
         * 
         * @return int is the id of the creator
         */
        int getIdCreator() const { return _idCreator; };

    private:
        int _idCreator;
};

/**
 * @brief The E_Player class is the player entity.
 */
class E_Player : public Entity {
    public:
        /**
         * @brief the constructor of the class E_Player with params
         *
         * During this constructor the different components that make up the entity will be created
         *
         * @param position_x The position_x is the bullet position on the x axis.
         * @param position_y The position_y is the bullet position on the y axis.
         * @param size_x The size_x is the bullet size on the x axis of the entity.
         * @param size_y The size_y is the bullet size on the y axis of the entity.
         * @param _lastTick The _lastTick is the last tick when the player shot
         */
        E_Player(int position_x, int position_y, float size_x, float size_y);

        /**
         * @brief is the update of the player
         * 
         */
        void update() override;

        /**
         * @brief Get the Type object
         * 
         * @return std::string is the type of the entity
         */
        std::string getType() const override;

        /**
         * @brief serialize the entity to a vector
         * 
         * @return std::vector<char> is the vector of the entity
         */
        std::vector<char> serializeToVector() override;

        /**
         * @brief Get the Last Tick object
         * 
         * @return int is the last tick when the player shot
         */
        int getLastTick() const { return _lastTick; };

        /**
         * @brief Set the Last Tick object
         * 
         * @param lastTick is the last tick when the player shot
         */
        void setLastTick(int lastTick) { _lastTick = lastTick; };
    private:
        int _lastTick = 0;
};

/**
 * @brief The E_Enemy class is the enemy entity.
 */
class E_Enemy : public Entity {
    public:
        /**
         * @brief the constructor of the class E_Enemy with params
         *
         * During this constructor the different components that make up the entity will be created
         *
         * @param position_x The position_x is the bullet position on the x axis.
         * @param position_y The position_y is the bullet position on the y axis.
         * @param size_x The size_x is the bullet size on the x axis of the entity.
         * @param size_y The size_y is the bullet size on the y axis of the entity.
         * @param tmp The tmp is the enemy type.
         */
        E_Enemy(int position_x, int position_y, float size_x, float size_y, int tmp);

        /**
         * @brief is the update of the enemy
         * 
         */
        void update() override;

        /**
         * @brief Get the Type object
         * 
         * @return std::string is the type of the entity
         */
        std::string getType() const override;

        /**
         * @brief serialize the entity to a vector
         * 
         * @return std::vector<char> is the vector of the entity
         */
        std::vector<char> serializeToVector() override;
};

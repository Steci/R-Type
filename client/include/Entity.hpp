/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"

/**
 * @brief The E_Bullet class is the bullet entity.
*/
class E_Bullet : public Entity {
    public:
        /**
         * @brief the constructor of the class E_Bullet with params.
         *
         * During this constructor the different components that make up the entity will be created.
         *
         * @param damage The damage is the bullet damage.
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         * @param velocity_x The velocity_x is the bullet velocity on the x axe of the entity.
         * @param velocity_y The velocity_y is the bullet velocity on the y axe of the entity.
         * @param idCreator The idCreator is this int allows you to know who created this bullet.
        */
        E_Bullet(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y, int idCreator);

        /**
         * @brief the constructor of the class E_Bullet in default.
         *
        */
        E_Bullet() = default;

        /**
         * @brief update the entity.
         *
        */
        void update() override {};

        /**
         * @brief displays the components that make up the entity.
         *
        */
        void render() override;

        /**
         * @brief get the type of the entity.
         *
         * @return std::string with the type entity.
        */
        std::string getType() const override;

        /**
         * @brief calls the deserialize functions of the components that make up the entity.
         *
         * @param data data is the vector with serializer data.
        */
        void deserializeFromVector(std::vector<char> data) override;

        /**
         * @brief retrieve the id of its creator.
         *
         * @return the int of its creator.
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
         * @brief the constructor of the class E_Player with params.
         *
         * During this constructor the different components that make up the entity will be created.
         *
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
        */
        E_Player(int position_x, int position_y, float size_x, float size_y);

        /**
         * @brief update the entity.
         *
        */
        void update() override;

        /**
         * @brief displays the components that make up the entity.
         *
        */
        void render() override;

        /**
         * @brief get the type of the entity.
         *
         * @return std::string with the type entity.
        */
        std::string getType() const override;

        /**
         * @brief calls the deserialize functions of the components that make up the entity.
         *
         * @param data data is the vector with serializer data.
        */
        void deserializeFromVector(std::vector<char> data) override;
};

/**
 * @brief The E_Enemy class is the enemy entity.
*/
class E_Enemy : public Entity {
    public:
        /**
         * @brief the constructor of the class E_Enemy with params.
         *
         * During this constructor the different components that make up the entity will be created.
         *
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         * @param tmp The tmp is the enemy type.
         */
        E_Enemy(int position_x, int position_y, float size_x, float size_y, int type);

        /**
         * @brief update the entity.
         *
        */
        void update() override;

        /**
         * @brief displays the components that make up the entity.
         *
        */
        void render() override;

        /**
         * @brief get the type of the entity.
         *
         * @return std::string with the type entity.
        */
        std::string getType() const override;

        /**
         * @brief calls the deserialize functions of the components that make up the entity.
         *
         * @param data data is the vector with serializer data.
        */
        void deserializeFromVector(std::vector<char> data) override;
};

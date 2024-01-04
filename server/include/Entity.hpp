/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"

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
         * @param path The path is the asset.
         * @param damage The damage is the bullet damage.
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         * @param velocity_x The velocity_x is the bullet velocity on the x axe of the entity.
         * @param velocity_y The velocity_y is the bullet velocity on the y axe of the entity.
         */
        E_Bullet(std::string path, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
        void update() override {};
        void render() override;
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
         * @param path The path is the asset.
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         */
        E_Player(std::string path, int position_x, int position_y, float size_x, float size_y);
        void update() override;
        void render() override;

        /**
         * @brief this function of the class new E_Bullet with params in this entity in the std::vector
         *
         * @param path The path is the asset.
         * @param damage The damage is the bullet damage.
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         * @param velocity_x The velocity_x is the bullet velocity on the x axe of the entity.
         * @param velocity_y The velocity_y is the bullet velocity on the y axe of the entity.
         */
        void newShoot(std::string path, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
    private:
        std::vector<std::unique_ptr<E_Bullet>> _bullets; /**< The list of E_Bullet classes in this entity. */
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
         * @param path The path is the asset.
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         */
        E_Enemy(std::string path, int position_x, int position_y, float size_x, float size_y);
        void update() override;
        void render() override;

        /**
         * @brief this function of the class new E_Bullet with params in this entity in the std::vector
         *
         * @param path The path is the asset.
         * @param damage The damage is the bullet damage.
         * @param position_x The position_x is the bullet position on the x axe.
         * @param position_y The position_y is the bullet position on the y axe.
         * @param size_x The size_x is the bullet size on the x axe of the entity.
         * @param size_y The size_y is the bullet size on the y axe of the entity.
         * @param velocity_x The velocity_x is the bullet velocity on the x axe of the entity.
         * @param velocity_y The velocity_y is the bullet velocity on the y axe of the entity.
         */
        void newShoot(std::string path, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
    private:
        std::vector<std::unique_ptr<E_Bullet>> _bullets; /**< The list of E_Bullet classes in this entity. */
};

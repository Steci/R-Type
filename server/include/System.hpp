/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#include "Engine.hpp"
#include "EngineSystem.hpp"

/**
 * @brief The S_EnemyAI class is the enemy ai system.
 * 
 */
class S_EnemyAI : public System {
    public:
        /**
         * @brief Construct a new s enemyai object
         * 
         * @param sparseEntities is the sparse array of entities
         */
        S_EnemyAI(SparseArray<IEntity> &sparseEntities);

        /**
         * @brief Destroy the s enemyai object
         * 
         */
        ~S_EnemyAI() = default;

        /**
         * @brief update the enemy ai
         * 
         */
        void update() override; 
    private:
        SparseArray<IEntity> &_sparseEntities;
};

/**
 * @brief The S_Spawner class is the spawner system.
 * 
 */
class S_Spawner : public System {
    public:
        /**
         * @brief Construct a new s spawner object
         * 
         * @param sparseEntities is the sparse array of entities
         */
        S_Spawner(SparseArray<IEntity> &sparseEntities);

        /**
         * @brief Destroy the s spawner object
         * 
         */
        ~S_Spawner() = default;

        /**
         * @brief update the spawner
         * 
         */
        void update() override;
    private:
        SparseArray<IEntity> &_sparseEntities;
};


/**
 * @brief The S_Collision class is the collision system.
 * 
 */
class S_Collision : public System {
    public:
        /**
         * @brief Construct a new s collision object
         * 
         * @param sparseEntities is the sparse array of entities
         */
        S_Collision(SparseArray<IEntity> &sparseEntities);
        
        /**
         * @brief Destroy the s collision object
         * 
         */
        ~S_Collision() = default;

        /**
         * @brief update the collision
         * 
         */
        void update() override;

        /**
         * @brief check if there is a collision
         * 
         * @param transform1 is The Transform Component of the first entity
         * @param transform2 is The Transform Component of the second entity
         * @param hitbox1 is The Hitbox Component of the first entity
         * @param hitbox2 is The Hitbox Component of the second entity 
         * @return true if there is a collision
         * @return false if there is no collision
         */
        bool checkCollision(C_Transform *transform1, C_Transform *transform2, C_Hitbox *hitbox1, C_Hitbox *hitbox2);
        int screenWidth = 800;
        int screenHeight = 600;
    private:
        SparseArray<IEntity> &_sparseEntities;
};

/**
 * @brief The S_Weapon class is the weapon system.
 * 
 */
class S_Weapon : public System {
    public:
        /**
         * @brief Construct a new s weapon object
         * 
         * @param sparseEntities is the sparse array of entities
         * @param tick is the tick
         */
        S_Weapon(SparseArray<IEntity> &sparseEntities, int &tick);

        /**
         * @brief Destroy the s weapon object
         * 
         */
        ~S_Weapon() = default;

        /**
         * @brief update the weapon
         * 
         */
        void update();

        /**
         * @brief shoot the player
         * 
         * @param idCreator is the id of the creator
         */
        void shootPlayer(int idCreator);

        /**
         * @brief Get the Firing Speed object
         * 
         * @return int is the firing speed
         */
        int getFiringSpeed() const { return _firingSpeed; };
        /**
         * @brief Set the Firing Speed object
         * 
         * @param firingSpeed is the firing speed
         */
        void setFiringSpeed(int firingSpeed) { _firingSpeed = firingSpeed; };

    private:
        int _firingSpeed = 40;
        SparseArray<IEntity> &_sparseEntities;
        int &_tick;
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"

class S_EnemyAI : public System {
    public:
        S_EnemyAI(SparseArray<IEntity> &sparseEntities);
        ~S_EnemyAI() = default;
        void update() override;
    private:
        SparseArray<IEntity> &_sparseEntities;
};

class S_Spawner : public System {
    public:
        S_Spawner(SparseArray<IEntity> &sparseEntities);
        ~S_Spawner() = default;
        void update() override;
    private:
        SparseArray<IEntity> &_sparseEntities;
};

class S_Collision : public System {
    public:
        S_Collision(SparseArray<IEntity> &sparseEntities);
        ~S_Collision() = default;
        void update() override;
        bool checkCollision(C_Transform *transform1, C_Transform *transform2, C_Hitbox *hitbox1, C_Hitbox *hitbox2);
        int screenWidth = 800;
        int screenHeight = 600;
    private:
        SparseArray<IEntity> &_sparseEntities;
};

class S_Weapon : public System {
   public:
       S_Weapon(SparseArray<IEntity> &sparseEntities, int &tick);
       ~S_Weapon() = default;
       void update();
       void shootPlayer(int idCreator);
       int getLastTick() {return _lastTick;};

   private:
       SparseArray<IEntity> &_sparseEntities;
       int &_tick;
       int _lastTick = 0;
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#include "Engine.hpp"
#include "SystemS.hpp"

class E_Bullet : public Entity {
    public:
        E_Bullet(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
        void update() override {}
        void render() override;
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override {}
};

class E_Player : public Entity {
    public:
        E_Player(std::string path, int position_x, int position_y, float size_x, float size_y);
        void update() override;
        void render() override;
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override;
    private:
        std::vector<std::unique_ptr<E_Bullet>> _bullets;
};

class E_Enemy : public Entity {
    public:
        E_Enemy(std::string path, int position_x, int position_y, float size_x, float size_y);
        void update() override;
        void render() override;
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override;
    private:
        std::vector<std::unique_ptr<E_Bullet>> _bullets;
};

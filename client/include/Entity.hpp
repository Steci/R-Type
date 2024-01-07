/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include "../../engine/include/Engine.hpp"
#include "../../engine/include/System.hpp"

class E_Bullet : public Entity {
    public:
        E_Bullet(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
        E_Bullet() = default;
        void update() override {};
        void render() override;
        std::vector<char> serializeToVector() override;
        void deserializeFromVector(std::vector<char> data) override;
};

class E_Player : public Entity {
    public:
        E_Player(int position_x, int position_y, float size_x, float size_y);
        void update() override;
        void render() override;
        void newShoot(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
        std::vector<char> serializeToVector() override;
        void deserializeFromVector(std::vector<char> data) override;
    private:
        std::vector<std::shared_ptr<E_Bullet>> _bullets;
};

class E_Enemy : public Entity {
    public:
        E_Enemy(int position_x, int position_y, float size_x, float size_y);
        void update() override;
        void render() override;
        void newShoot(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y);
        std::vector<char> serializeToVector() override;
        void deserializeFromVector(std::vector<char> data) override;
    private:
        std::vector<std::shared_ptr<E_Bullet>> _bullets;
};

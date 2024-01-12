/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include "Engine.hpp"
#include "EngineSystem.hpp"

class E_Bullet : public Entity {
    public:
        E_Bullet(int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y, int idCreator);
        E_Bullet() = default;
        void update() override {};
        std::string getType() const override;
        std::vector<char> serializeToVector() override;
        int getIdCreator() const { return _idCreator; };

    private:
        int _idCreator;
};

class E_Player : public Entity {
    public:
        E_Player(int position_x, int position_y, float size_x, float size_y);
        void update() override;
        std::string getType() const override;
        std::vector<char> serializeToVector() override;
};

class E_Enemy : public Entity {
    public:
        E_Enemy(int position_x, int position_y, float size_x, float size_y, int type);
        void update() override;
        std::string getType() const override;
        std::vector<char> serializeToVector() override;
};

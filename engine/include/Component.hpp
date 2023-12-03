/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include "Utils.hpp"

class IComponent {
    public:
        virtual ~IComponent() = default;
        virtual std::string getName();
};

class AComponent : public IComponent {
    public:
        const std:string getName() override {
            return _name;
        }
    private:
        std::string _name;
}

class Transform : public AComponent {
    public:
        Transform() = default;
        Transform(float pos_x, float pos_y, float rot_x, float rot_y) : _position(pos_x, pos_y),  _rotation_x(rot_x, rot_y) {};
        ~Transform() = default;

        const Vec2 getPosition() {
            return _position;
        }
        const Vec2 getRotation() {
            return _rotation;
        }
        void setPosition(float pos_x, float pos_y) {
            _position.x = pos_x;
            _position.y = pos_y;
        }
        void setRotation(float rot_x, float rot_y) {
            _rotation.x = rot_x;
            _rotation.y = rot_y;
        }
    private:
        Vec2 _position;
        Vec2 _rotation;
}

class Health : public AComponent {
    public:
        Health() = default;
        Health(int health) : _health(health) {};
        ~Health() = default;

        const int getHealth() {
            return _health;
        }
        void setHealth(int health) {
            _health = health;
        }
    private:
        int _health;
}

class Weapon : public AComponent {
    public:
        Weapon() = default;
        Weapon(std::string name, int damage) : _name(name), _damage(damage) {};
        ~Weapon() = default;

        const std::string getName() {
            return _name;
        }
        const int getDamage() {
            return _damage;
        }
        void setName(std::string name) {
            _name = name;
        }
        void setDamage(int damage) {
            _damage = damage;
        }
    private:
        std::string _name;
        int _damage;
}

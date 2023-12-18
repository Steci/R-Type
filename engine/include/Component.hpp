/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <raylib.h>

#include "Utils.hpp"

// TODO : Voir avec Axel ce qu'il a mis en Component

struct Component {
    virtual ~Component() = default;
};

struct C_Transform : public Component {
    Vec2 _position;
    Vec2 _rotation;
};

struct C_Damage : public Component {
    std::string _name;
    int _damage;
};

struct C_Health : public Component {
    int _health;
};

struct C_Sprite : public Component {
    std::string _name;
    Texture2D _sprite;
};

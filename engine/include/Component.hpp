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

#include "Utils/Vector2.hpp"

// TODO : Voir avec Axel ce qu'il a mis en Component

struct Component {
    virtual ~Component() = default;
};

struct C_Transform : public Component {
    Engine::Vector2<float> _position = {0, 0};
    Engine::Vector2<float> _rotation = {0, 0};
};

struct C_Damage : public Component {
    std::string _name;
    int _damage;
};

struct C_Health : public Component {
    int _health = 100;
};

struct C_Sprite : public Component {
    std::string _name;
    Texture2D _sprite = LoadTexture("assets/placeholder.png"); //TODO: use resources manager
};

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

#include "Utils.hpp"

// TODO : Voir avec Axel ce qu'il a mis en Component

struct C_Transform {
    Vec2 _position;
    Vec2 _rotation;
};

struct C_Damage {
    std::string _name;
    int _damage;
};

struct C_Health {
    int _health;
};

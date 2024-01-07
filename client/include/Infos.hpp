/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Infos.hpp
*/

#pragma once

#include <string>
#include <iostream>

#include "../../engine/include/Utils.hpp"

struct Infos {
    Vec2 _size;
    std::string _name;
    Infos(float size_x, float size_y, std::string name) {
        _size = {size_x, size_y};
        _name = name;
    }
    Infos() = default;
    ~Infos() = default;
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Infos.hpp
*/

#pragma once

#include <string>
#include <iostream>
#include <raylib.h>

#include "EngineUtils.hpp"

struct Infos {
    Vec2 _size;
    Texture2D _texture;
    Image _image;
    Infos(float size_x, float size_y, std::string name) {
        _size = {size_x, size_y};
        Image _image = LoadImage(name.c_str());
        if (_image.data == nullptr) {
            std::cerr << "Erreur de chargement de l'image : " << name << std::endl;
        } else {
            _texture = LoadTextureFromImage(_image);
        }
    }
    Infos() = default;
    ~Infos() = default;
};

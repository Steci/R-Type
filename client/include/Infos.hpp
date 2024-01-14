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

/**
 * @brief The Infos class is the class that contains the information of the entity.
*/
struct Infos {
    Vec2 _size;
    Texture2D _texture;
    Image _image;

    /**
     * @brief Construct a new Infos object
     * 
     * @param size_x is the size on the x axis
     * @param size_y is the size on the y axis
     * @param name is the name of the image
     */
    Infos(float size_x, float size_y, std::string name) {
        _size = {size_x, size_y};
        Image _image = LoadImage(name.c_str());
        if (_image.data == nullptr) {
            std::cerr << "Erreur de chargement de l'image : " << name << std::endl;
        } else {
            _texture = LoadTextureFromImage(_image);
        }
    }

    /**
     * @brief Construct a new Infos object
     * 
     */
    Infos() = default;

    /**
     * @brief Destroy the Infos object
     * 
     */
    ~Infos() {
        //printf("Merde\n");
        //if (_image.data != nullptr) {
        //    printf("Merde1\n");
        //    UnloadImage(_image);
        //}
        //if (_texture.id != 0) {
        //    printf("Merde2\n");
        //    UnloadTexture(_texture);
        //}
    }
};

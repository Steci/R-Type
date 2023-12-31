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
#include <list>

#include "Utils.hpp"

// TODO : Voir avec Axel ce qu'il a mis en Component

/**
 * @brief The base class for all components in the engine.
 *
 * This struct serves as the base class for all components in the engine.
 * It provides a virtual destructor to ensure proper cleanup when derived
 * components are destroyed.
 */
struct Component {
    virtual ~Component() = default;
};

/**
 * @brief The C_Transform struct represents a transform component.
 *
 * This component stores the position and rotation of an entity in 2D space.
 */
struct C_Transform : public Component {
    Vec2 _position; /**< The position of the entity. */
    Vec2 _size; /**< The rotation of the entity. */
    Vec2 _velocity;
    int _animation;
    C_Transform(int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) {
        _position = {position_x, position_y};
        _size = {size_x, size_y};
        _animation = 0;
        _velocity.x = velocity_x;
        _velocity.y = velocity_y;
    }
    ~C_Transform() = default;
};

/**
 * @brief The C_Damage struct represents a component that stores information about damage.
 */
struct C_Damage : public Component {
    int _damage; /**< The amount of damage. */
    C_Damage(int damage) {
        _damage = damage;
    }
    ~C_Damage() = default;
};

/**
 * @brief The C_Health struct represents a component that stores information about health.
 */
struct C_Health : public Component {
    int _health;
    C_Health(int health) {
        _health = health;
    }
    ~C_Health() = default;
};

/**
 * @brief The C_Sprite struct represents a component that stores information about a sprite.
 */
struct C_Sprite : public Component {
    std::string _name;
    Image _image;
    Texture2D _texture;
    C_Sprite(const std::string& imagePath) {
        _image = LoadImage(imagePath.c_str());
        if (_image.data == nullptr) {
            std::cerr << "Erreur de chargement de l'image : " << imagePath << std::endl;
        } else {
            _texture = LoadTextureFromImage(_image);
        }
    }
    ~C_Sprite() {
        UnloadTexture(_texture);
        UnloadImage(_image);
    }
    C_Sprite(const C_Sprite&) = delete;
    C_Sprite& operator=(const C_Sprite&) = delete;
};

/**
 * @brief The C_Hitbox struct represents a component that stores information about a hitbox.
 */
struct C_Hitbox : public Component {
    Vec2 _size;
    int _time;
    int _status;
    C_Hitbox(int x, int y) {
        _size = {x, y};
        _time = 10;
        _status = 0;
    }
    ~C_Hitbox() = default;
};

struct C_Score : public Component {
    int _score;
    C_Score() {
        _score = 0;
    }
    ~C_Score() = default;
};

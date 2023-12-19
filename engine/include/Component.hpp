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
    Vec2 _position = {0, 0}; /**< The position of the entity. */
    Vec2 _rotation = {0, 0}; /**< The rotation of the entity. */
};

/**
 * @brief The C_Damage struct represents a component that stores information about damage.
 */
struct C_Damage : public Component {
    std::string _name; /**< The name of the damage component. */
    int _damage; /**< The amount of damage. */
};

/**
 * @brief The C_Health struct represents a component that stores information about health.
 */
struct C_Health : public Component {
    int _health = 100;
};

/**
 * @brief The C_Sprite struct represents a component that stores information about a sprite.
 */
struct C_Sprite : public Component {
    ~C_Sprite() {
        UnloadTexture(_sprite);
    }
    std::string _name;
    Texture2D _sprite = LoadTexture("assets/placeholder.png");
};

/**
 * @brief The C_Hitbox struct represents a component that stores information about a hitbox.
 */
struct C_Hitbox : public Component {
    Vec2 _size = {0, 0};
};

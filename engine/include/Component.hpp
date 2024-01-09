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
#include <cstring>

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
    std::vector<char> serializeToVector() const {
        std::vector<char> data;
        std::vector<char> position = _position.serializeToVector();
        std::vector<char> size = _size.serializeToVector();
        std::vector<char> velocity = _velocity.serializeToVector();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), size.begin(), size.end());
        data.insert(data.end(), reinterpret_cast<const char*>(&_animation), reinterpret_cast<const char*>(&_animation) + sizeof(_animation));
        return data;
    }
    void deserializeFromVector(const std::vector<char>& data) {
        _position.deserializeFromVector(std::vector<char>(data.begin(), data.begin() + sizeof(_position)));
        _size.deserializeFromVector(std::vector<char>(data.begin() + sizeof(_position), data.begin() + sizeof(_position) + sizeof(_size)));
        _velocity.deserializeFromVector(std::vector<char>(data.begin() + sizeof(_position) + sizeof(_size), data.begin() + sizeof(_position) + sizeof(_size) + sizeof(_velocity)));
        std::memcpy(&_animation, data.data() + sizeof(_position) + sizeof(_size) + sizeof(_velocity), sizeof(_animation));
    }
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
    std::vector<char> serializeToVector() const {
        return std::vector<char>(reinterpret_cast<const char*>(&_damage), reinterpret_cast<const char*>(&_damage) + sizeof(_damage));
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&_damage, data.data(), sizeof(_damage));
    }
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
    std::vector<char> serializeToVector() const {
        return std::vector<char>(reinterpret_cast<const char*>(&_health), reinterpret_cast<const char*>(&_health) + sizeof(_health));
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&_health, data.data(), sizeof(_health));
    }
};

/**
 * @brief The C_Sprite struct represents a component that stores information about a sprite.
 */
struct C_Sprite : public Component {
    std::string _name;
    Image _image;
    Texture2D _texture;
    C_Sprite() = default;
    void setupByPath(const std::string& imagePath) {
        _image = LoadImage(imagePath.c_str());
        if (_image.data == nullptr) {
            std::cerr << "Erreur de chargement de l'image : " << imagePath << std::endl;
        } else {
            _texture = LoadTextureFromImage(_image);
        }
    }
    void setupByTexture(Texture2D texture)
    {
        _texture = texture;
    }
    ~C_Sprite() = default;
    C_Sprite(const C_Sprite&) = delete;
    C_Sprite& operator=(const C_Sprite&) = delete;
    std::vector<char> serializeToVector() const {
        std::vector<char> data(_name.begin(), _name.end());
        return data;
    }
    void deserializeFromVector(const std::vector<char>& data) {
        _name = std::string(data.begin(), data.end());
    }
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
    std::vector<char> serializeToVector() const {
        std::vector<char> data;
        data.insert(data.end(), reinterpret_cast<const char*>(&_size), reinterpret_cast<const char*>(&_size) + sizeof(_size));
        data.insert(data.end(), reinterpret_cast<const char*>(&_time), reinterpret_cast<const char*>(&_time) + sizeof(_time));
        data.insert(data.end(), reinterpret_cast<const char*>(&_status), reinterpret_cast<const char*>(&_status) + sizeof(_status));
        return data;
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&_size, data.data(), sizeof(_size));
        std::memcpy(&_time, data.data() + sizeof(_size), sizeof(_time));
        std::memcpy(&_status, data.data() + sizeof(_size) + sizeof(_time), sizeof(_status));
    }
};

struct C_Score : public Component {
    int _score;
    C_Score() {
        _score = 0;
    }
    ~C_Score() = default;
    std::vector<char> serializeToVector() const {
        return std::vector<char>(reinterpret_cast<const char*>(&_score), reinterpret_cast<const char*>(&_score) + sizeof(_score));
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&_score, data.data(), sizeof(_score));
    }
};

struct C_EnemyInfo : public Component {
    int _type;
    C_EnemyInfo(int type) {
        _type = type;
    }
    ~C_EnemyInfo() = default;
    std::vector<char> serializeToVector() const {
        return std::vector<char>(reinterpret_cast<const char*>(&_type), reinterpret_cast<const char*>(&_type) + sizeof(_type));
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&_type, data.data(), sizeof(_type));
    }
};

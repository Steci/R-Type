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

#include "EngineUtils.hpp"

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
    Vec2 _size; /**< The size of the entity. */
    Vec2 _velocity; /**< The velocity of the entity. */
    int _animation; /**< The animation of the entity. */
    C_Transform(float position_x, float position_y, float size_x, float size_y, float velocity_x, float velocity_y) {
        _position = {position_x, position_y};
        _size = {size_x, size_y};
        _velocity.x = velocity_x;
        _velocity.y = velocity_y;
        _animation = 0;
    }
    ~C_Transform() = default;
    std::vector<char> serializeToVector() const {
        std::vector<char> data;
        std::vector<char> position = _position.serializeToVector();
        std::vector<char> size = _size.serializeToVector();
        std::vector<char> velocity = _velocity.serializeToVector();
        data.insert(data.end(), position.begin(), position.end());
        data.insert(data.end(), size.begin(), size.end());
        data.insert(data.end(), velocity.begin(), velocity.end());
        data.insert(data.end(), reinterpret_cast<const char*>(&_animation), reinterpret_cast<const char*>(&_animation) + sizeof(_animation));
        return data;
    }
    void deserializeFromVector(const std::vector<char>& data) {
        _position.deserializeFromVector(std::vector<char>(data.begin(), data.begin() + sizeof(_position)));
        _size.deserializeFromVector(std::vector<char>(data.begin() + sizeof(_position), data.begin() + sizeof(_position) + sizeof(_size)));
        _velocity.deserializeFromVector(std::vector<char>(data.begin() + sizeof(_position) + sizeof(_size), data.begin() + sizeof(_position) + sizeof(_size) + sizeof(_velocity)));
        std::memcpy(&_animation, data.data() + sizeof(_position) + sizeof(_size) + sizeof(_velocity), sizeof(_animation));
    }
    bool operator==(const C_Transform& other) const {
        return _position == other._position && _size == other._size && 
           _velocity == other._velocity && _animation == other._animation;
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
    bool operator==(const C_Damage& other) const {
        return _damage == other._damage;
    }
};

/**
 * @brief The C_Health struct represents a component that stores information about health.
 */
struct C_Health : public Component {
    int _health; /**< The amount of health. */
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
    bool operator==(const C_Health& other) const {
        return _health == other._health;
    }
};

/**
 * @brief The C_Sprite struct represents a component that stores information about a sprite.
 */
struct C_Sprite : public Component {
    std::string _name; /**< The asset path to use. */
    Image _image; /**< The Image of the asset. */
    Texture2D _texture; /**< The Texture2D of the asset. */
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
    bool operator==(const C_Sprite& other) const {
        return _name == other._name;
    }
};

/**
 * @brief The C_Hitbox struct represents a component that stores information about a hitbox.
 */
struct C_Hitbox : public Component {
    Vec2 _size; /**< The size of the collision box of this entity. */
    int _time; /**< The entity key state duration. */
    int _status; /**< The status of the entity's collision box. */
    C_Hitbox(float x, float y) {
        _size = {x, y};
        _time = 10;
        _status = 0;
    }
    ~C_Hitbox() = default;
    std::vector<char> serializeToVector() const {
        std::vector<char> data;
        std::vector<char> size = _size.serializeToVector();
        data.insert(data.end(), size.begin(), size.end());
        data.insert(data.end(), reinterpret_cast<const char*>(&_time), reinterpret_cast<const char*>(&_time) + sizeof(_time));
        data.insert(data.end(), reinterpret_cast<const char*>(&_status), reinterpret_cast<const char*>(&_status) + sizeof(_status));
        return data;
    }
    void deserializeFromVector(const std::vector<char>& data) {
        _size.deserializeFromVector(std::vector<char>(data.begin(), data.begin() + sizeof(_size)));
        std::memcpy(&_time, data.data() + sizeof(_size), sizeof(_time));
        std::memcpy(&_status, data.data() + sizeof(_size) + sizeof(_time), sizeof(_status));
    }
    bool operator==(const C_Hitbox& other) const {
        return _size == other._size && _time == other._time && _status == other._status;
    }
};

/**
 * @brief The C_Score struct represents the score of player during the game.
 */
struct C_Score : public Component {
    int score; /**< The amount of score. */
    C_Score() {
        score = 0;
    }
    ~C_Score() = default;
    std::vector<char> serializeToVector() const {
        return std::vector<char>(reinterpret_cast<const char*>(&score), reinterpret_cast<const char*>(&score) + sizeof(score));
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&score, data.data(), sizeof(score));
    }
    bool operator==(const C_Score& other) const {
        return score == other.score;
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
    bool operator==(const C_EnemyInfo& other) const {
        return _type == other._type;
    }
};

struct C_AnimationInfo : public Component {
    Vec2 _size;
    int _maxXframe;
    int _maxYframe;
    int _framesCounter = 0;
    int _currentFrame = 0;
    int _speed;
    C_AnimationInfo(int x, int y, int maxXframe, int maxYframe, int speed) {
        _size = {static_cast<float>(x), static_cast<float>(y)};
        _maxXframe = maxXframe;
        _maxYframe = maxYframe;
        _speed = speed;
    }
    ~C_AnimationInfo() = default;
    std::vector<char> serializeToVector() const {
        std::vector<char> data;
        data.insert(data.end(), reinterpret_cast<const char*>(&_size), reinterpret_cast<const char*>(&_size) + sizeof(_size));
        data.insert(data.end(), reinterpret_cast<const char*>(&_maxXframe), reinterpret_cast<const char*>(&_maxXframe) + sizeof(_maxXframe));
        data.insert(data.end(), reinterpret_cast<const char*>(&_maxYframe), reinterpret_cast<const char*>(&_maxYframe) + sizeof(_maxYframe));
        data.insert(data.end(), reinterpret_cast<const char*>(&_speed), reinterpret_cast<const char*>(&_speed) + sizeof(_speed));
        return data;
    }
    void deserializeFromVector(const std::vector<char>& data) {
        std::memcpy(&_size, data.data(), sizeof(_size));
        std::memcpy(&_maxXframe, data.data() + sizeof(_size), sizeof(_maxXframe));
        std::memcpy(&_maxYframe, data.data() + sizeof(_size) + sizeof(_maxXframe), sizeof(_maxYframe));
    }
    bool operator==(const C_AnimationInfo& other) const {
        return _size == other._size && _maxXframe == other._maxXframe && 
               _maxYframe == other._maxYframe && _speed == other._speed;
    }
};
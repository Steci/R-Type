/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Utils.hpp
*/

#pragma once
/**
 * @brief The class for setup Vector2 for the different components.
 */
class Vec2 {
    public:
        float x, y;

        Vec2() : x(0), y(0) {};
        Vec2(float x, float y) : x(x), y(y) {};
        ~Vec2() = default;
        std::vector<char> serializeToVector() const {
            std::vector<char> data;
            data.insert(data.end(), reinterpret_cast<const char*>(&x), reinterpret_cast<const char*>(&x) + sizeof(x));
            data.insert(data.end(), reinterpret_cast<const char*>(&y), reinterpret_cast<const char*>(&y) + sizeof(y));
            return data;
        }
        void deserializeFromVector(const std::vector<char>& data) {
            std::memcpy(&x, data.data(), sizeof(x));
            std::memcpy(&y, data.data() + sizeof(x), sizeof(y));
        }
};

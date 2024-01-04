/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Utils.hpp
*/

/**
 * @brief The class for setup Vector2 for the different components.
 */
class Vec2 {
    public:
        float x, y;

        Vec2() : x(0), y(0) {};
        Vec2(float x, float y) : x(x), y(y) {};
        ~Vec2() = default;
};

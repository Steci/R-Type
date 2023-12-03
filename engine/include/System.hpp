/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#pragma once
#include <memory>

class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void update() = 0;
};

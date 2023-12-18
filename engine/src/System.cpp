/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.cpp
*/

#include "System.hpp"

// This function will have to be called in a while loop controling the closing on the other side
void S_Renderer::render()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(_camera);
            for (auto& entity : _entities) {
                entity->render();
            }
        EndMode2D();
    EndDrawing();
}

void S_Renderer::update()
{
    while (!WindowShouldClose()) {
        render();
    }
}
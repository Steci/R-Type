/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include "Engine.hpp"


int main(void)
{
    SystemManager manager;

    manager.addSystem<S_Renderer>(800, 600, 60, "Game");
    manager.addSystem<S_Collision>();

    IEntity *enemy = new E_Enemy("assets/placeholder.png");
    IEntity *player =   new E_Player();

    // Add the entity to the system
    manager.getSystem<S_Renderer>()->addEntity(enemy);
    manager.getSystem<S_Renderer>()->addEntity(player);

    // Modify the entity's components
    C_Transform* transform = getComponentRef<C_Transform>(*player);
    transform->_position = {200, 200};

    while (1) {
        if(IsKeyDown(KEY_RIGHT)) {
            transform->_position.x += 3;
        }
        if (IsKeyDown(KEY_LEFT)) {
            transform->_position.x -= 3;
        }
        if (IsKeyDown(KEY_UP)) {
            transform->_position.y -= 3;
        }
        if (IsKeyDown(KEY_DOWN)) {
            transform->_position.y += 3;
        }
        if (manager.getSystem<S_Collision>()->checkCollision(player, enemy)) {
            std::cout << "Collision !" << std::endl;
        }
        manager.update();
    };

    return 0;
}
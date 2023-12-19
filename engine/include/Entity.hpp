/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include "Component.hpp"

class IEntity {
    public:
        virtual ~IEntity() = default;
        // The update method is called every frame
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void addComponent(std::unique_ptr<Component> component) = 0;
        virtual void removeComponent(Component* component) = 0;
        virtual std::vector<std::unique_ptr<Component>>& getComponents() = 0;
        virtual Component* getComponentOfType(const std::type_info& ti) = 0;
};

class AbstractEntity : public IEntity {
    public:
        void update() override = 0;
        void render() override = 0;
        void addComponent(std::unique_ptr<Component> component) override {
            components.push_back(std::move(component));
        }
        void removeComponent(Component* component) override {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (it->get() == component) {
                    components.erase(it);
                    return;
                }
            }
        }
        std::vector<std::unique_ptr<Component>>& getComponents() override {
            return components;
        }
        Component* getComponentOfType(const std::type_info& ti) override {
            for (auto& component : components) {
                if (typeid(*component) == ti) {
                    return component.get();
                }
            }
            return nullptr;
        }
    private:
        std::vector<std::unique_ptr<Component>> components;
};

class E_Player : public AbstractEntity {
    public:
        E_Player() {
            C_Transform transform;
            C_Health health;
            C_Sprite sprite;
            C_Hitbox hitbox;
            hitbox._size = {50, 50};
            addComponent(std::make_unique<C_Transform>(transform));
            addComponent(std::make_unique<C_Health>(health));
            addComponent(std::make_unique<C_Sprite>(sprite));
            addComponent(std::make_unique<C_Hitbox>(hitbox));
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
        }
        void render() override {
            int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
            int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
            int squareSize = 50;
            DrawRectangle(xPos, yPos, squareSize, squareSize, BLUE);
        }
};

class E_Enemy : public AbstractEntity {
    public:
        E_Enemy(std::string path) {
            C_Transform transform;
            C_Health health;
            C_Sprite sprite;
            C_Hitbox hitbox;
            hitbox._size = {50, 50};
            sprite._sprite = LoadTexture(path.c_str());
            addComponent(std::make_unique<C_Transform>(transform));
            addComponent(std::make_unique<C_Health>(health));
            addComponent(std::make_unique<C_Sprite>(sprite));
            addComponent(std::make_unique<C_Hitbox>(hitbox));
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
        }
        void render() override {
            auto& transform = getComponents()[0];
            int xPos = dynamic_cast<C_Transform*>(transform.get())->_position.x;
            int yPos = dynamic_cast<C_Transform*>(transform.get())->_position.y;
            int squareSize = 50;
            DrawRectangle(xPos, yPos, squareSize, squareSize, RED);
        }
};

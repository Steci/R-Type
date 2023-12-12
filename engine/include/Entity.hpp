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
        virtual void addComponent(std::unique_ptr<IComponent> component) = 0;
        virtual void removeComponent(IComponent* component) = 0;
        virtual std::vector<std::unique_ptr<IComponent>>& getComponents() = 0;
};

class AbstractEntity : public IEntity {
    public:
        void update() override = 0;
        void render() override = 0;
        void addComponent(std::unique_ptr<IComponent> component) override {
            components.push_back(std::move(component));
        }
        void removeComponent(IComponent* component) override {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (it->get() == component) {
                    components.erase(it);
                    return;
                }
            }
        }
        std::vector<std::unique_ptr<IComponent>>& getComponents() override {
            return components;
        }
    private:
        std::vector<std::unique_ptr<IComponent>> components;
};

class E_Enemy : public AbstractEntity {
    public:
        E_Enemy() {
            addComponent(std::make_unique<C_Transform>(0, 0, 0, 0));
            addComponent(std::make_unique<C_Health>(100));
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
            std::cout << "Enemy position: " << dynamic_cast<C_Transform*>(transform.get())->getPosition().x << std::endl;
            std::cout << "Enemy health: " << dynamic_cast<C_Health*>(health.get())->getHealth() << std::endl;
        }
        void render() override {
            std::cout << "Enemy render" << std::endl;
        }
};

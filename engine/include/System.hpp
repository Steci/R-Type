/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#pragma once
#include <memory>
#include <vector>
#include "Entity.hpp"

class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void update() = 0;
    protected:
        std::vector<std::unique_ptr<IEntity>> _entities;
};

class ASystem : public ISystem {
    public:
        void update() override = 0;
        void addEntity(std::unique_ptr<IEntity> entity) {
            _entities.push_back(std::move(entity));
        }
        void removeEntity(IEntity* entity) {
            for (auto it = _entities.begin(); it != _entities.end(); it++) {
                if (it->get() == entity) {
                    _entities.erase(it);
                    return;
                }
            }
        }
};

class SystemManager {
    public:
        template<typename T>
        void addSystem(std::unique_ptr<T> system) {
            _systems.push_back(std::move(system));
        }

        // TODO : FIX THIS, SEND BACK REFERENCE INSTEAD OF POINTER
        template<typename T>
        T* getSystem() {
            for (auto& system : _systems) {
                if (dynamic_cast<T*>(system.get()))
                    return dynamic_cast<T*>(system.get());
            }
            return nullptr;
        }
        void update() {
            for (auto& system : _systems) {
                system->update();
            }
        }
    private:
        std::vector<std::unique_ptr<ISystem>> _systems;
};

// TODO : IMPLEMENT AN EVENT SYSTEM (MAP OF EVENTS)

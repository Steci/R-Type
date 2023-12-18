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

        template<typename T>
        ISystem &getSystem() {
            for (auto& system : _systems) {
                if (dynamic_cast<T*>(system.get()))
                    system.get();
            }
            return *_systems[0];
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

class S_Renderer : public ASystem {
    public:
        S_Renderer(int w, int h, int fps, const char* wName) {
            _screenWidth = w;
            _screenHeight = h;
            _targetFps = fps;
            _windowName = wName;
            InitWindow(_screenWidth, _screenHeight, _windowName);
            SetTargetFPS(_targetFps);
            // not sure if this is usefull
            // _camera = { 0 };
        };

        void update() override;

        void render();

    private:
        int _screenWidth;
        int _screenHeight;
        int _targetFps;
        const char* _windowName;

        Camera2D _camera;
};

class S_AudioManager : public ASystem {
};

class S_EnemyAI : public ASystem {
};

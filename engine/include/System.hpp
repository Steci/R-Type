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
        template<typename T, typename... Args>
        void addSystem(Args&&... args) {
            _systems.push_back(new T(std::forward<Args>(args)...));
        }

        template<typename T>
        T* getSystem() {
            for (auto& system : _systems) {
                if (typeid(*system) == typeid(T)) {
                    return dynamic_cast<T*>(system);
                }
            }
            return nullptr;
        }

        void update() {
            for (auto& system : _systems) {
                system->update();
            }
        }

        ~SystemManager() {
        }

    private:
        std::vector<ISystem*> _systems;
};

// TODO : IMPLEMENT AN EVENT SYSTEM (MAP OF EVENTS)

class S_Renderer : public ASystem {
    public:
        S_Renderer(int w, int h, int fps, std::string wName) {
            _screenWidth = w;
            _screenHeight = h;
            _targetFps = fps;
            _windowName = wName;
            InitWindow(_screenWidth, _screenHeight, _windowName.c_str());
            SetTargetFPS(_targetFps);
        };

        void render()
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

        void update() override
        {
            if (IsKeyPressed(KEY_ESCAPE))
                closeWindow();
            if (!WindowShouldClose())
                render();
        }

        void closeWindow()
        {
            CloseWindow();
        }

    private:
        int _screenWidth;
        int _screenHeight;
        int _targetFps;
        std::string _windowName;

        Camera2D _camera;
};

class S_Network : public ASystem {
};

class S_AudioManager : public ASystem {
};

class S_EnemyAI : public ASystem {
};

class S_Collision : public ASystem {
};

class S_Animation : public ASystem {
};
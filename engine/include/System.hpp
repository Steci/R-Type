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
        std::vector<IEntity*> _entities;
};

class ASystem : public ISystem {
    public:
        void update() override = 0;
        void addEntity(IEntity* entity) {
            _entities.push_back(entity);
        }
        void removeEntity(IEntity* entity) {
            for (auto it = _entities.begin(); it != _entities.end(); it++) {
                if (*it == entity) {
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
                for (auto& entity : _entities) {
                    entity->render();
                }
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
    public:
        void update() override
        {

        };

        bool checkCollision(IEntity* entity1, IEntity* entity2)
        {
            C_Hitbox *hitbox1 = getComponentRef<C_Hitbox>(*entity1);
            C_Hitbox *hitbox2 = getComponentRef<C_Hitbox>(*entity2);
            C_Transform *transform1 = getComponentRef<C_Transform>(*entity1);
            C_Transform *transform2 = getComponentRef<C_Transform>(*entity2);

            if (transform1->_position.x < transform2->_position.x + hitbox2->_size.x &&
                transform1->_position.x + hitbox1->_size.x > transform2->_position.x &&
                transform1->_position.y < transform2->_position.y + hitbox2->_size.y &&
                transform1->_position.y + hitbox1->_size.y > transform2->_position.y)
                return true;
            return false;
        };
};

class S_Animation : public ASystem {
};
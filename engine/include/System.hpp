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

/**
 * @brief The base interface for all systems in the engine.
 */
class ISystem {
    public:
        /**
         * @brief Virtual destructor for ISystem.
         */
        virtual ~ISystem() = default;

        /**
         * @brief Update function for the system.
         */
        virtual void update() = 0;

    protected:
        std::vector<IEntity*> _entities; /**< The list of entities managed by the system. */
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

/**
 * @brief The SystemManager class manages a collection of systems.
 */
class SystemManager {
    public:
        /**
         * @brief Adds a new system to the collection.
         *
         * @tparam T The type of the system to add.
         * @tparam Args The types of the arguments to pass to the system's constructor.
         * @param args The arguments to pass to the system's constructor.
         */
        template<typename T, typename... Args>
        void addSystem(Args&&... args) {
            _systems.push_back(new T(std::forward<Args>(args)...));
        }

        /**
         * @brief Retrieves a system of the specified type.
         *
         * @tparam T The type of the system to retrieve.
         * @return A pointer to the system if found, nullptr otherwise.
         */
        template<typename T>
        T* getSystem() {
            for (auto& system : _systems) {
                if (typeid(*system) == typeid(T)) {
                    return dynamic_cast<T*>(system);
                }
            }
            return nullptr;
        }

        /**
         * @brief Updates all systems in the collection.
         */
        void update() {
            for (auto& system : _systems) {
                system->update();
            }
        }

        /**
         * @brief Destructor for the SystemManager class.
         */
        ~SystemManager() {
        }

    private:
        std::vector<ISystem*> _systems; /**< The collection of systems managed by the SystemManager. */
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
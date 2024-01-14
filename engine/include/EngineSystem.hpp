/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System.hpp
*/

#pragma once

#include "EngineEntity.hpp"
#include "Engine.hpp"
#include <map>

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

class System : public ISystem {
    public:
        System() = default;
        ~System() = default;
        void update() override = 0;
        void addEntity(IEntity* entity);
        void removeEntity(IEntity* entity);
        void clearEntities() { _entities.clear(); };
};

/**
 * @brief The SystemManager class manages a collection of systems.
 */
class SystemManager {
    public:
        /**
        * @brief Destructor for the SystemManager class.
        */
        SystemManager() = default;
        ~SystemManager() = default;
        /**
         * @brief Adds a new system to the collection.
         *
         * @tparam T The type of the system to add.
         * @tparam Args The types of the arguments to pass to the system's constructor.
         * @param args The arguments to pass to the system's constructor.
         */
        template<typename T, typename... Args>
        void addSystem(Args&&... args)
        {
            _systems.push_back(new T(std::forward<Args>(args)...));
        }

        /**
         * @brief Retrieves a system of the specified type.
         *
         * @tparam T The type of the system to retrieve.
         * @return A pointer to the system if found, nullptr otherwise.
         */
        template<typename T>
        T* getSystem()
        {
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
        void update();
    private:
        std::vector<ISystem*> _systems; /**< The collection of systems managed by the SystemManager. */
};

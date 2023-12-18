/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine.hpp
*/

#pragma once

#include <vector>
#include <cassert>

#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "ResourcesManager.hpp"


namespace Engine
{
    // -------------- CONTEXT -------------- //

    static SystemManager _systemManager;

    static ResourcesManager rManager;

    // ---------------------------- ENTITY ---------------------------- //

    /**
     * @brief Create a Enemy object
     * 
     * @param args ???
     * @return true if the enemy is created
    */
    bool CreateEnemy(/*args*/)
    {
        if (_systemManager.getSystem<S_Player>() == nullptr)
            _systemManager.getSystem<S_Renderer>()->addEntity(std::make_unique<E_Enemy>(/*args*/));
        return true;
    }

    /**
     * @brief Create a Player object
     * 
     * @param args ???
     * @return true if the player is created
    */
    bool CreatePlayer(/*args*/)
    {
        if (_systemManager.getSystem<S_Player>() == nullptr)
            _systemManager.getSystem<S_Renderer>()->addEntity(std::make_unique<E_Player>(/*args*/));
        return true;
    }

    // TODO: Delete player ???


    // TODO: Delete enemy ???

    // --------------------------- COMPONENT -------------------------- //


    // ---------------------------- SYSTEM ---------------------------- //

    /**
     * @brief Create a Window object
     * 
     * @param width is the width of the window
     * @param height is the height of the window
     * @param fps is the fps of the window
     * @param title is the title of the window
    */
    bool CreateWindow(int width, int height, int fps, const char *title)
    {
        if (_systemManager.getSystem<S_Window>() == nullptr)
            _systemManager.addSystem<S_Window>(width, height, fps, title);
        else
            _systemManager.getSystem<S_Window>()->setWindow(width, height, fps, title);

        return true;
    }

    // TODO: Create Network System

    // TODO: Create Audio System

    // TODO: Create EnemyAI System

    // TODO: Create Collision System

    // TODO: Create Animation System
    
    // ---------------------------- Sparse Array ---------------------------- //
    
    // TODO: Create Sparse Array ???

}

// Sparse Array
template<typename T>
class SparseArray {
    public:
        void add(int id, const T& element) {
            if (id >= sparse.size()) {
                sparse.resize(id + 1, -1);
            }

            if (sparse[id] == -1) {
                sparse[id] = dense.size();
                dense.push_back(element);
                indices.push_back(id);
            } else {
                // Replace if already exists
                dense[sparse[id]] = element;
            }
        }

        void remove(int id) {
            assert(id < sparse.size() && sparse[id] != -1 && "Invalid ID");

            int denseIndex = sparse[id];
            int lastIndex = dense.size() - 1;
            int lastID = indices[lastIndex];

            std::swap(dense[denseIndex], dense[lastIndex]);
            std::swap(indices[denseIndex], indices[lastIndex]);

            sparse[lastID] = denseIndex;
            sparse[id] = -1;

            dense.pop_back();
            indices.pop_back();
        }

        T& get(int id) {
            assert(id < sparse.size() && sparse[id] != -1 && "Invalid ID");
            return dense[sparse[id]];
        }

        bool exists(int id) const {
            return id < sparse.size() && sparse[id] != -1;
        }

    private:
        std::vector<T> dense; // Stores actual elements
        std::vector<int> sparse; // Maps IDs to indices in 'dense'
        std::vector<int> indices; // Stores original IDs
};

// Usage
// SparseArray<YourEntityType> entities;
// entities.add(entityId, entity);


// TODO : IMPLEMENT RESSOURCE MANAGER

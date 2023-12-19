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
